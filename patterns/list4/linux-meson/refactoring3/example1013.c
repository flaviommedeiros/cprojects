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

		case OP_31_XOP_TRAP:
#ifdef CONFIG_64BIT
		case OP_31_XOP_TRAP_64:
#endif
#ifdef CONFIG_PPC_BOOK3S
			kvmppc_core_queue_program(vcpu, SRR1_PROGTRAP);
#else
			kvmppc_core_queue_program(vcpu,
					vcpu->arch.shared->esr | ESR_PTR);
#endif
			advance = 0;
			break;
		case OP_31_XOP_LWZX:
			emulated = kvmppc_handle_load(run, vcpu, rt, 4, 1);
			break;

		case OP_31_XOP_LBZX:
			emulated = kvmppc_handle_load(run, vcpu, rt, 1, 1);
			break;

		case OP_31_XOP_LBZUX:
			emulated = kvmppc_handle_load(run, vcpu, rt, 1, 1);
			kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
			break;

		case OP_31_XOP_STWX:
			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               4, 1);
			break;

		case OP_31_XOP_STBX:
			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               1, 1);
			break;

		case OP_31_XOP_STBUX:
			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               1, 1);
			kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
			break;

		case OP_31_XOP_LHAX:
			emulated = kvmppc_handle_loads(run, vcpu, rt, 2, 1);
			break;

		case OP_31_XOP_LHZX:
			emulated = kvmppc_handle_load(run, vcpu, rt, 2, 1);
			break;

		case OP_31_XOP_LHZUX:
			emulated = kvmppc_handle_load(run, vcpu, rt, 2, 1);
			kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
			break;

		case OP_31_XOP_MFSPR:
			emulated = kvmppc_emulate_mfspr(vcpu, sprn, rt);
			break;

		case OP_31_XOP_STHX:
			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               2, 1);
			break;

		case OP_31_XOP_STHUX:
			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               2, 1);
			kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
			break;

		case OP_31_XOP_MTSPR:
			emulated = kvmppc_emulate_mtspr(vcpu, sprn, rs);
			break;

		case OP_31_XOP_DCBST:
		case OP_31_XOP_DCBF:
		case OP_31_XOP_DCBI:
			/* Do nothing. The guest is performing dcbi because
			 * hardware DMA is not snooped by the dcache, but
			 * emulated DMA either goes through the dcache as
			 * normal writes, or the host kernel has handled dcache
			 * coherence. */
			break;

		case OP_31_XOP_LWBRX:
			emulated = kvmppc_handle_load(run, vcpu, rt, 4, 0);
			break;

		case OP_31_XOP_TLBSYNC:
			break;

		case OP_31_XOP_STWBRX:
			emulated = kvmppc_handle_store(run, vcpu,
						       kvmppc_get_gpr(vcpu, rs),
			                               4, 0);
			break;

		case OP_31_XOP_LHBRX:
			emulated = kvmppc_handle_load(run, vcpu, rt, 2, 0);
			break;

		case OP_31_XOP_STHBRX:
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
		emulated = kvmppc_handle_load(run, vcpu, rt, 4, 1);
		break;

	/* TBD: Add support for other 64 bit load variants like ldu, ldux, ldx etc. */
	case OP_LD:
		rt = get_rt(inst);
		emulated = kvmppc_handle_load(run, vcpu, rt, 8, 1);
		break;

	case OP_LWZU:
		emulated = kvmppc_handle_load(run, vcpu, rt, 4, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
		break;

	case OP_LBZ:
		emulated = kvmppc_handle_load(run, vcpu, rt, 1, 1);
		break;

	case OP_LBZU:
		emulated = kvmppc_handle_load(run, vcpu, rt, 1, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
		break;

	case OP_STW:
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               4, 1);
		break;

	/* TBD: Add support for other 64 bit store variants like stdu, stdux, stdx etc. */
	case OP_STD:
		rs = get_rs(inst);
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               8, 1);
		break;

	case OP_STWU:
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               4, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
		break;

	case OP_STB:
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               1, 1);
		break;

	case OP_STBU:
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               1, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
		break;

	case OP_LHZ:
		emulated = kvmppc_handle_load(run, vcpu, rt, 2, 1);
		break;

	case OP_LHZU:
		emulated = kvmppc_handle_load(run, vcpu, rt, 2, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
		break;

	case OP_LHA:
		emulated = kvmppc_handle_loads(run, vcpu, rt, 2, 1);
		break;

	case OP_LHAU:
		emulated = kvmppc_handle_loads(run, vcpu, rt, 2, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
		break;

	case OP_STH:
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               2, 1);
		break;

	case OP_STHU:
		emulated = kvmppc_handle_store(run, vcpu,
					       kvmppc_get_gpr(vcpu, rs),
		                               2, 1);
		kvmppc_set_gpr(vcpu, ra, vcpu->arch.vaddr_accessed);
		break;

	default:
		emulated = EMULATE_FAIL;
	}
