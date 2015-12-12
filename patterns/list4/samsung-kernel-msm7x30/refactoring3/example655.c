switch (get_op(inst)) {
	case OP_TRAP:
#ifdef CONFIG_PPC_BOOK3S
	case OP_TRAP_64:
		kvmppc_core_queue_program(vcpu, SRR1_PROGTRAP);
#else
		kvmppc_core_queue_program(vcpu,
					  vcpu->arch.shared->esr | ESR_PTR);
#endif
		advance = 0;
		break;

	case 31:
		switch (get_xop(inst)) {

		case OP_31_XOP_LWZX:
			rt = get_rt(inst);
			emulated = kvmppc_handle_load(run, vcpu, rt, 4, 1);
			break;

		case OP_31_XOP_LBZX:
			rt = get_rt(inst);
			emulated = kvmppc_handle_load(run, vcpu, rt, 1, 1);
			break;

		case OP_31_XOP_LBZUX:
			rt = get_rt(inst);
			ra = get_ra(inst);
			rb = get_rb(inst);

			ea = kvmppc_get_gpr(vcpu, rb);
			if (ra)
				ea += kvmppc_get_gpr(vcpu, ra);

			emulated = kvmppc_handle_load(run, vcpu, rt, 1, 1);
			kvmppc_set_gpr(vcpu, ra, ea);
			break;

		case OP_31_XOP_STWX:
			rs = get_rs(inst);
			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               4, 1);
			break;

		case OP_31_XOP_STBX:
			rs = get_rs(inst);
			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               1, 1);
			break;

		case OP_31_XOP_STBUX:
			rs = get_rs(inst);
			ra = get_ra(inst);
			rb = get_rb(inst);

			ea = kvmppc_get_gpr(vcpu, rb);
			if (ra)
				ea += kvmppc_get_gpr(vcpu, ra);

			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               1, 1);
			kvmppc_set_gpr(vcpu, rs, ea);
			break;

		case OP_31_XOP_LHAX:
			rt = get_rt(inst);
			emulated = kvmppc_handle_loads(run, vcpu, rt, 2, 1);
			break;

		case OP_31_XOP_LHZX:
			rt = get_rt(inst);
			emulated = kvmppc_handle_load(run, vcpu, rt, 2, 1);
			break;

		case OP_31_XOP_LHZUX:
			rt = get_rt(inst);
			ra = get_ra(inst);
			rb = get_rb(inst);

			ea = kvmppc_get_gpr(vcpu, rb);
			if (ra)
				ea += kvmppc_get_gpr(vcpu, ra);

			emulated = kvmppc_handle_load(run, vcpu, rt, 2, 1);
			kvmppc_set_gpr(vcpu, ra, ea);
			break;

		case OP_31_XOP_MFSPR:
			sprn = get_sprn(inst);
			rt = get_rt(inst);

			switch (sprn) {
			case SPRN_SRR0:
				kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->srr0);
				break;
			case SPRN_SRR1:
				kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->srr1);
				break;
			case SPRN_PVR:
				kvmppc_set_gpr(vcpu, rt, vcpu->arch.pvr); break;
			case SPRN_PIR:
				kvmppc_set_gpr(vcpu, rt, vcpu->vcpu_id); break;
			case SPRN_MSSSR0:
				kvmppc_set_gpr(vcpu, rt, 0); break;

			/* Note: mftb and TBRL/TBWL are user-accessible, so
			 * the guest can always access the real TB anyways.
			 * In fact, we probably will never see these traps. */
			case SPRN_TBWL:
				kvmppc_set_gpr(vcpu, rt, get_tb() >> 32); break;
			case SPRN_TBWU:
				kvmppc_set_gpr(vcpu, rt, get_tb()); break;

			case SPRN_SPRG0:
				kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->sprg0);
				break;
			case SPRN_SPRG1:
				kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->sprg1);
				break;
			case SPRN_SPRG2:
				kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->sprg2);
				break;
			case SPRN_SPRG3:
				kvmppc_set_gpr(vcpu, rt, vcpu->arch.shared->sprg3);
				break;
			/* Note: SPRG4-7 are user-readable, so we don't get
			 * a trap. */

			case SPRN_DEC:
			{
				kvmppc_set_gpr(vcpu, rt,
					       kvmppc_get_dec(vcpu, get_tb()));
				break;
			}
			default:
				emulated = kvmppc_core_emulate_mfspr(vcpu, sprn, rt);
				if (emulated == EMULATE_FAIL) {
					printk("mfspr: unknown spr %x\n", sprn);
					kvmppc_set_gpr(vcpu, rt, 0);
				}
				break;
			}
			kvmppc_set_exit_type(vcpu, EMULATED_MFSPR_EXITS);
			break;

		case OP_31_XOP_STHX:
			rs = get_rs(inst);
			ra = get_ra(inst);
			rb = get_rb(inst);

			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               2, 1);
			break;

		case OP_31_XOP_STHUX:
			rs = get_rs(inst);
			ra = get_ra(inst);
			rb = get_rb(inst);

			ea = kvmppc_get_gpr(vcpu, rb);
			if (ra)
				ea += kvmppc_get_gpr(vcpu, ra);

			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               2, 1);
			kvmppc_set_gpr(vcpu, ra, ea);
			break;

		case OP_31_XOP_MTSPR:
			sprn = get_sprn(inst);
			rs = get_rs(inst);
			switch (sprn) {
			case SPRN_SRR0:
				vcpu->arch.shared->srr0 = kvmppc_get_gpr(vcpu, rs);
				break;
			case SPRN_SRR1:
				vcpu->arch.shared->srr1 = kvmppc_get_gpr(vcpu, rs);
				break;

			/* XXX We need to context-switch the timebase for
			 * watchdog and FIT. */
			case SPRN_TBWL: break;
			case SPRN_TBWU: break;

			case SPRN_MSSSR0: break;

			case SPRN_DEC:
				vcpu->arch.dec = kvmppc_get_gpr(vcpu, rs);
				kvmppc_emulate_dec(vcpu);
				break;

			case SPRN_SPRG0:
				vcpu->arch.shared->sprg0 = kvmppc_get_gpr(vcpu, rs);
				break;
			case SPRN_SPRG1:
				vcpu->arch.shared->sprg1 = kvmppc_get_gpr(vcpu, rs);
				break;
			case SPRN_SPRG2:
				vcpu->arch.shared->sprg2 = kvmppc_get_gpr(vcpu, rs);
				break;
			case SPRN_SPRG3:
				vcpu->arch.shared->sprg3 = kvmppc_get_gpr(vcpu, rs);
				break;

			default:
				emulated = kvmppc_core_emulate_mtspr(vcpu, sprn, rs);
				if (emulated == EMULATE_FAIL)
					printk("mtspr: unknown spr %x\n", sprn);
				break;
			}
			kvmppc_set_exit_type(vcpu, EMULATED_MTSPR_EXITS);
			break;

		case OP_31_XOP_DCBF:
		case OP_31_XOP_DCBI:
			/* Do nothing. The guest is performing dcbi because
			 * hardware DMA is not snooped by the dcache, but
			 * emulated DMA either goes through the dcache as
			 * normal writes, or the host kernel has handled dcache
			 * coherence. */
			break;

		case OP_31_XOP_LWBRX:
			rt = get_rt(inst);
			emulated = kvmppc_handle_load(run, vcpu, rt, 4, 0);
			break;

		case OP_31_XOP_TLBSYNC:
			break;

		case OP_31_XOP_STWBRX:
			rs = get_rs(inst);
			ra = get_ra(inst);
			rb = get_rb(inst);

			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               4, 0);
			break;

		case OP_31_XOP_LHBRX:
			rt = get_rt(inst);
			emulated = kvmppc_handle_load(run, vcpu, rt, 2, 0);
			break;

		case OP_31_XOP_STHBRX:
			rs = get_rs(inst);
			ra = get_ra(inst);
			rb = get_rb(inst);

			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               2, 0);
			break;

		default:
			/* Attempt core-specific emulation below. */
			emulated = EMULATE_FAIL;
		}
		break;

	case OP_LWZ:
		rt = get_rt(inst);
		emulated = kvmppc_handle_load(run, vcpu, rt, 4, 1);
		break;

	case OP_LWZU:
		ra = get_ra(inst);
		rt = get_rt(inst);
		emulated = kvmppc_handle_load(run, vcpu, rt, 4, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.paddr_accessed);
		break;

	case OP_LBZ:
		rt = get_rt(inst);
		emulated = kvmppc_handle_load(run, vcpu, rt, 1, 1);
		break;

	case OP_LBZU:
		ra = get_ra(inst);
		rt = get_rt(inst);
		emulated = kvmppc_handle_load(run, vcpu, rt, 1, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.paddr_accessed);
		break;

	case OP_STW:
		rs = get_rs(inst);
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               4, 1);
		break;

	case OP_STWU:
		ra = get_ra(inst);
		rs = get_rs(inst);
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               4, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.paddr_accessed);
		break;

	case OP_STB:
		rs = get_rs(inst);
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               1, 1);
		break;

	case OP_STBU:
		ra = get_ra(inst);
		rs = get_rs(inst);
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               1, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.paddr_accessed);
		break;

	case OP_LHZ:
		rt = get_rt(inst);
		emulated = kvmppc_handle_load(run, vcpu, rt, 2, 1);
		break;

	case OP_LHZU:
		ra = get_ra(inst);
		rt = get_rt(inst);
		emulated = kvmppc_handle_load(run, vcpu, rt, 2, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.paddr_accessed);
		break;

	case OP_LHA:
		rt = get_rt(inst);
		emulated = kvmppc_handle_loads(run, vcpu, rt, 2, 1);
		break;

	case OP_LHAU:
		ra = get_ra(inst);
		rt = get_rt(inst);
		emulated = kvmppc_handle_loads(run, vcpu, rt, 2, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.paddr_accessed);
		break;

	case OP_STH:
		rs = get_rs(inst);
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               2, 1);
		break;

	case OP_STHU:
		ra = get_ra(inst);
		rs = get_rs(inst);
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               2, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.paddr_accessed);
		break;

	default:
		emulated = EMULATE_FAIL;
	}
