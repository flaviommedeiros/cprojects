switch (get_xop(inst)) {
		case OP_31_XOP_MFMSR:
			kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->msr);
			break;
		case OP_31_XOP_MTMSRD:
		{
			ulong rs_val = kvmppc_get_gpr(vcpu, rs);
			if (inst & 0x10000) {
				ulong new_msr = vcpu->arch.shared->msr;
				new_msr &= ~(MSR_RI | MSR_EE);
				new_msr |= rs_val & (MSR_RI | MSR_EE);
				vcpu->arch.shared->msr = new_msr;
			} else
				kvmppc_set_msr(vcpu, rs_val);
			break;
		}
		case OP_31_XOP_MTMSR:
			kvmppc_set_msr(vcpu, kvmppc_get_gpr(vcpu, rs));
			break;
		case OP_31_XOP_MFSR:
		{
			int srnum;

			srnum = kvmppc_get_field(inst, 12 + 32, 15 + 32);
			if (vcpu->arch.mmu.mfsrin) {
				u32 sr;
				sr = vcpu->arch.mmu.mfsrin(vcpu, srnum);
				kvmppc_set_gpr(vcpu, rt, sr);
			}
			break;
		}
		case OP_31_XOP_MFSRIN:
		{
			int srnum;

			srnum = (kvmppc_get_gpr(vcpu, rb) >> 28) & 0xf;
			if (vcpu->arch.mmu.mfsrin) {
				u32 sr;
				sr = vcpu->arch.mmu.mfsrin(vcpu, srnum);
				kvmppc_set_gpr(vcpu, rt, sr);
			}
			break;
		}
		case OP_31_XOP_MTSR:
			vcpu->arch.mmu.mtsrin(vcpu,
				(inst >> 16) & 0xf,
				kvmppc_get_gpr(vcpu, rs));
			break;
		case OP_31_XOP_MTSRIN:
			vcpu->arch.mmu.mtsrin(vcpu,
				(kvmppc_get_gpr(vcpu, rb) >> 28) & 0xf,
				kvmppc_get_gpr(vcpu, rs));
			break;
		case OP_31_XOP_TLBIE:
		case OP_31_XOP_TLBIEL:
		{
			bool large = (inst & 0x00200000) ? true : false;
			ulong addr = kvmppc_get_gpr(vcpu, rb);
			vcpu->arch.mmu.tlbie(vcpu, addr, large);
			break;
		}
#ifdef CONFIG_KVM_BOOK3S_64_PR
		case OP_31_XOP_FAKE_SC1:
		{
			/* SC 1 papr hypercalls */
			ulong cmd = kvmppc_get_gpr(vcpu, 3);
			int i;

		        if ((vcpu->arch.shared->msr & MSR_PR) ||
			    !vcpu->arch.papr_enabled) {
				emulated = EMULATE_FAIL;
				break;
			}

			if (kvmppc_h_pr(vcpu, cmd) == EMULATE_DONE)
				break;

			run->papr_hcall.nr = cmd;
			for (i = 0; i < 9; ++i) {
				ulong gpr = kvmppc_get_gpr(vcpu, 4 + i);
				run->papr_hcall.args[i] = gpr;
			}

			run->exit_reason = KVM_EXIT_PAPR_HCALL;
			vcpu->arch.hcall_needed = 1;
			emulated = EMULATE_EXIT_USER;
			break;
		}
#endif
		case OP_31_XOP_EIOIO:
			break;
		case OP_31_XOP_SLBMTE:
			if (!vcpu->arch.mmu.slbmte)
				return EMULATE_FAIL;

			vcpu->arch.mmu.slbmte(vcpu,
					kvmppc_get_gpr(vcpu, rs),
					kvmppc_get_gpr(vcpu, rb));
			break;
		case OP_31_XOP_SLBIE:
			if (!vcpu->arch.mmu.slbie)
				return EMULATE_FAIL;

			vcpu->arch.mmu.slbie(vcpu,
					kvmppc_get_gpr(vcpu, rb));
			break;
		case OP_31_XOP_SLBIA:
			if (!vcpu->arch.mmu.slbia)
				return EMULATE_FAIL;

			vcpu->arch.mmu.slbia(vcpu);
			break;
		case OP_31_XOP_SLBMFEE:
			if (!vcpu->arch.mmu.slbmfee) {
				emulated = EMULATE_FAIL;
			} else {
				ulong t, rb_val;

				rb_val = kvmppc_get_gpr(vcpu, rb);
				t = vcpu->arch.mmu.slbmfee(vcpu, rb_val);
				kvmppc_set_gpr(vcpu, rt, t);
			}
			break;
		case OP_31_XOP_SLBMFEV:
			if (!vcpu->arch.mmu.slbmfev) {
				emulated = EMULATE_FAIL;
			} else {
				ulong t, rb_val;

				rb_val = kvmppc_get_gpr(vcpu, rb);
				t = vcpu->arch.mmu.slbmfev(vcpu, rb_val);
				kvmppc_set_gpr(vcpu, rt, t);
			}
			break;
		case OP_31_XOP_DCBA:
			/* Gets treated as NOP */
			break;
		case OP_31_XOP_DCBZ:
		{
			ulong rb_val = kvmppc_get_gpr(vcpu, rb);
			ulong ra_val = 0;
			ulong addr, vaddr;
			u32 zeros[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
			u32 dsisr;
			int r;

			if (ra)
				ra_val = kvmppc_get_gpr(vcpu, ra);

			addr = (ra_val + rb_val) & ~31ULL;
			if (!(vcpu->arch.shared->msr & MSR_SF))
				addr &= 0xffffffff;
			vaddr = addr;

			r = kvmppc_st(vcpu, &addr, 32, zeros, true);
			if ((r == -ENOENT) || (r == -EPERM)) {
				struct kvmppc_book3s_shadow_vcpu *svcpu;

				svcpu = svcpu_get(vcpu);
				*advance = 0;
				vcpu->arch.shared->dar = vaddr;
				svcpu->fault_dar = vaddr;

				dsisr = DSISR_ISSTORE;
				if (r == -ENOENT)
					dsisr |= DSISR_NOHPTE;
				else if (r == -EPERM)
					dsisr |= DSISR_PROTFAULT;

				vcpu->arch.shared->dsisr = dsisr;
				svcpu->fault_dsisr = dsisr;
				svcpu_put(svcpu);

				kvmppc_book3s_queue_irqprio(vcpu,
					BOOK3S_INTERRUPT_DATA_STORAGE);
			}

			break;
		}
		default:
			emulated = EMULATE_FAIL;
		}
