switch (exit_nr) {
	case BOOK3S_INTERRUPT_INST_STORAGE:
	{
		ulong shadow_srr1 = vcpu->arch.shadow_srr1;
		vcpu->stat.pf_instruc++;

		if (kvmppc_is_split_real(vcpu))
			kvmppc_fixup_split_real(vcpu);

#ifdef CONFIG_PPC_BOOK3S_32
		/* We set segments as unused segments when invalidating them. So
		 * treat the respective fault as segment fault. */
		{
			struct kvmppc_book3s_shadow_vcpu *svcpu;
			u32 sr;

			svcpu = svcpu_get(vcpu);
			sr = svcpu->sr[kvmppc_get_pc(vcpu) >> SID_SHIFT];
			svcpu_put(svcpu);
			if (sr == SR_INVALID) {
				kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu));
				r = RESUME_GUEST;
				break;
			}
		}
#endif

		/* only care about PTEG not found errors, but leave NX alone */
		if (shadow_srr1 & 0x40000000) {
			int idx = srcu_read_lock(&vcpu->kvm->srcu);
			r = kvmppc_handle_pagefault(run, vcpu, kvmppc_get_pc(vcpu), exit_nr);
			srcu_read_unlock(&vcpu->kvm->srcu, idx);
			vcpu->stat.sp_instruc++;
		} else if (vcpu->arch.mmu.is_dcbz32(vcpu) &&
			  (!(vcpu->arch.hflags & BOOK3S_HFLAG_DCBZ32))) {
			/*
			 * XXX If we do the dcbz hack we use the NX bit to flush&patch the page,
			 *     so we can't use the NX bit inside the guest. Let's cross our fingers,
			 *     that no guest that needs the dcbz hack does NX.
			 */
			kvmppc_mmu_pte_flush(vcpu, kvmppc_get_pc(vcpu), ~0xFFFUL);
			r = RESUME_GUEST;
		} else {
			u64 msr = kvmppc_get_msr(vcpu);
			msr |= shadow_srr1 & 0x58000000;
			kvmppc_set_msr_fast(vcpu, msr);
			kvmppc_book3s_queue_irqprio(vcpu, exit_nr);
			r = RESUME_GUEST;
		}
		break;
	}
	case BOOK3S_INTERRUPT_DATA_STORAGE:
	{
		ulong dar = kvmppc_get_fault_dar(vcpu);
		u32 fault_dsisr = vcpu->arch.fault_dsisr;
		vcpu->stat.pf_storage++;

#ifdef CONFIG_PPC_BOOK3S_32
		/* We set segments as unused segments when invalidating them. So
		 * treat the respective fault as segment fault. */
		{
			struct kvmppc_book3s_shadow_vcpu *svcpu;
			u32 sr;

			svcpu = svcpu_get(vcpu);
			sr = svcpu->sr[dar >> SID_SHIFT];
			svcpu_put(svcpu);
			if (sr == SR_INVALID) {
				kvmppc_mmu_map_segment(vcpu, dar);
				r = RESUME_GUEST;
				break;
			}
		}
#endif

		/*
		 * We need to handle missing shadow PTEs, and
		 * protection faults due to us mapping a page read-only
		 * when the guest thinks it is writable.
		 */
		if (fault_dsisr & (DSISR_NOHPTE | DSISR_PROTFAULT)) {
			int idx = srcu_read_lock(&vcpu->kvm->srcu);
			r = kvmppc_handle_pagefault(run, vcpu, dar, exit_nr);
			srcu_read_unlock(&vcpu->kvm->srcu, idx);
		} else {
			kvmppc_set_dar(vcpu, dar);
			kvmppc_set_dsisr(vcpu, fault_dsisr);
			kvmppc_book3s_queue_irqprio(vcpu, exit_nr);
			r = RESUME_GUEST;
		}
		break;
	}
	case BOOK3S_INTERRUPT_DATA_SEGMENT:
		if (kvmppc_mmu_map_segment(vcpu, kvmppc_get_fault_dar(vcpu)) < 0) {
			kvmppc_set_dar(vcpu, kvmppc_get_fault_dar(vcpu));
			kvmppc_book3s_queue_irqprio(vcpu,
				BOOK3S_INTERRUPT_DATA_SEGMENT);
		}
		r = RESUME_GUEST;
		break;
	case BOOK3S_INTERRUPT_INST_SEGMENT:
		if (kvmppc_mmu_map_segment(vcpu, kvmppc_get_pc(vcpu)) < 0) {
			kvmppc_book3s_queue_irqprio(vcpu,
				BOOK3S_INTERRUPT_INST_SEGMENT);
		}
		r = RESUME_GUEST;
		break;
	/* We're good on these - the host merely wanted to get our attention */
	case BOOK3S_INTERRUPT_DECREMENTER:
	case BOOK3S_INTERRUPT_HV_DECREMENTER:
	case BOOK3S_INTERRUPT_DOORBELL:
	case BOOK3S_INTERRUPT_H_DOORBELL:
		vcpu->stat.dec_exits++;
		r = RESUME_GUEST;
		break;
	case BOOK3S_INTERRUPT_EXTERNAL:
	case BOOK3S_INTERRUPT_EXTERNAL_LEVEL:
	case BOOK3S_INTERRUPT_EXTERNAL_HV:
		vcpu->stat.ext_intr_exits++;
		r = RESUME_GUEST;
		break;
	case BOOK3S_INTERRUPT_PERFMON:
		r = RESUME_GUEST;
		break;
	case BOOK3S_INTERRUPT_PROGRAM:
	case BOOK3S_INTERRUPT_H_EMUL_ASSIST:
	{
		enum emulation_result er;
		ulong flags;
		u32 last_inst;
		int emul;

program_interrupt:
		flags = vcpu->arch.shadow_srr1 & 0x1f0000ull;

		emul = kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst);
		if (emul != EMULATE_DONE) {
			r = RESUME_GUEST;
			break;
		}

		if (kvmppc_get_msr(vcpu) & MSR_PR) {
#ifdef EXIT_DEBUG
			pr_info("Userspace triggered 0x700 exception at\n 0x%lx (0x%x)\n",
				kvmppc_get_pc(vcpu), last_inst);
#endif
			if ((last_inst & 0xff0007ff) !=
			    (INS_DCBZ & 0xfffffff7)) {
				kvmppc_core_queue_program(vcpu, flags);
				r = RESUME_GUEST;
				break;
			}
		}

		vcpu->stat.emulated_inst_exits++;
		er = kvmppc_emulate_instruction(run, vcpu);
		switch (er) {
		case EMULATE_DONE:
			r = RESUME_GUEST_NV;
			break;
		case EMULATE_AGAIN:
			r = RESUME_GUEST;
			break;
		case EMULATE_FAIL:
			printk(KERN_CRIT "%s: emulation at %lx failed (%08x)\n",
			       __func__, kvmppc_get_pc(vcpu), last_inst);
			kvmppc_core_queue_program(vcpu, flags);
			r = RESUME_GUEST;
			break;
		case EMULATE_DO_MMIO:
			run->exit_reason = KVM_EXIT_MMIO;
			r = RESUME_HOST_NV;
			break;
		case EMULATE_EXIT_USER:
			r = RESUME_HOST_NV;
			break;
		default:
			BUG();
		}
		break;
	}
	case BOOK3S_INTERRUPT_SYSCALL:
	{
		u32 last_sc;
		int emul;

		/* Get last sc for papr */
		if (vcpu->arch.papr_enabled) {
			/* The sc instuction points SRR0 to the next inst */
			emul = kvmppc_get_last_inst(vcpu, INST_SC, &last_sc);
			if (emul != EMULATE_DONE) {
				kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) - 4);
				r = RESUME_GUEST;
				break;
			}
		}

		if (vcpu->arch.papr_enabled &&
		    (last_sc == 0x44000022) &&
		    !(kvmppc_get_msr(vcpu) & MSR_PR)) {
			/* SC 1 papr hypercalls */
			ulong cmd = kvmppc_get_gpr(vcpu, 3);
			int i;

#ifdef CONFIG_PPC_BOOK3S_64
			if (kvmppc_h_pr(vcpu, cmd) == EMULATE_DONE) {
				r = RESUME_GUEST;
				break;
			}
#endif

			run->papr_hcall.nr = cmd;
			for (i = 0; i < 9; ++i) {
				ulong gpr = kvmppc_get_gpr(vcpu, 4 + i);
				run->papr_hcall.args[i] = gpr;
			}
			run->exit_reason = KVM_EXIT_PAPR_HCALL;
			vcpu->arch.hcall_needed = 1;
			r = RESUME_HOST;
		} else if (vcpu->arch.osi_enabled &&
		    (((u32)kvmppc_get_gpr(vcpu, 3)) == OSI_SC_MAGIC_R3) &&
		    (((u32)kvmppc_get_gpr(vcpu, 4)) == OSI_SC_MAGIC_R4)) {
			/* MOL hypercalls */
			u64 *gprs = run->osi.gprs;
			int i;

			run->exit_reason = KVM_EXIT_OSI;
			for (i = 0; i < 32; i++)
				gprs[i] = kvmppc_get_gpr(vcpu, i);
			vcpu->arch.osi_needed = 1;
			r = RESUME_HOST_NV;
		} else if (!(kvmppc_get_msr(vcpu) & MSR_PR) &&
		    (((u32)kvmppc_get_gpr(vcpu, 0)) == KVM_SC_MAGIC_R0)) {
			/* KVM PV hypercalls */
			kvmppc_set_gpr(vcpu, 3, kvmppc_kvm_pv(vcpu));
			r = RESUME_GUEST;
		} else {
			/* Guest syscalls */
			vcpu->stat.syscall_exits++;
			kvmppc_book3s_queue_irqprio(vcpu, exit_nr);
			r = RESUME_GUEST;
		}
		break;
	}
	case BOOK3S_INTERRUPT_FP_UNAVAIL:
	case BOOK3S_INTERRUPT_ALTIVEC:
	case BOOK3S_INTERRUPT_VSX:
	{
		int ext_msr = 0;
		int emul;
		u32 last_inst;

		if (vcpu->arch.hflags & BOOK3S_HFLAG_PAIRED_SINGLE) {
			/* Do paired single instruction emulation */
			emul = kvmppc_get_last_inst(vcpu, INST_GENERIC,
						    &last_inst);
			if (emul == EMULATE_DONE)
				goto program_interrupt;
			else
				r = RESUME_GUEST;

			break;
		}

		/* Enable external provider */
		switch (exit_nr) {
		case BOOK3S_INTERRUPT_FP_UNAVAIL:
			ext_msr = MSR_FP;
			break;

		case BOOK3S_INTERRUPT_ALTIVEC:
			ext_msr = MSR_VEC;
			break;

		case BOOK3S_INTERRUPT_VSX:
			ext_msr = MSR_VSX;
			break;
		}

		r = kvmppc_handle_ext(vcpu, exit_nr, ext_msr);
		break;
	}
	case BOOK3S_INTERRUPT_ALIGNMENT:
	{
		u32 last_inst;
		int emul = kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst);

		if (emul == EMULATE_DONE) {
			u32 dsisr;
			u64 dar;

			dsisr = kvmppc_alignment_dsisr(vcpu, last_inst);
			dar = kvmppc_alignment_dar(vcpu, last_inst);

			kvmppc_set_dsisr(vcpu, dsisr);
			kvmppc_set_dar(vcpu, dar);

			kvmppc_book3s_queue_irqprio(vcpu, exit_nr);
		}
		r = RESUME_GUEST;
		break;
	}
#ifdef CONFIG_PPC_BOOK3S_64
	case BOOK3S_INTERRUPT_FAC_UNAVAIL:
		kvmppc_handle_fac(vcpu, vcpu->arch.shadow_fscr >> 56);
		r = RESUME_GUEST;
		break;
#endif
	case BOOK3S_INTERRUPT_MACHINE_CHECK:
	case BOOK3S_INTERRUPT_TRACE:
		kvmppc_book3s_queue_irqprio(vcpu, exit_nr);
		r = RESUME_GUEST;
		break;
	default:
	{
		ulong shadow_srr1 = vcpu->arch.shadow_srr1;
		/* Ugh - bork here! What did we get? */
		printk(KERN_EMERG "exit_nr=0x%x | pc=0x%lx | msr=0x%lx\n",
			exit_nr, kvmppc_get_pc(vcpu), shadow_srr1);
		r = RESUME_HOST;
		BUG();
		break;
	}
	}
