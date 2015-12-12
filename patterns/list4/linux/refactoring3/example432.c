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

		case OP_31_XOP_MFSPR:
			emulated = kvmppc_emulate_mfspr(vcpu, sprn, rt);
			break;

		case OP_31_XOP_MTSPR:
			emulated = kvmppc_emulate_mtspr(vcpu, sprn, rs);
			break;

		case OP_31_XOP_TLBSYNC:
			break;

		default:
			/* Attempt core-specific emulation below. */
			emulated = EMULATE_FAIL;
		}
		break;

	case 0:
		/*
		 * Instruction with primary opcode 0. Based on PowerISA
		 * these are illegal instructions.
		 */
		if (inst == KVMPPC_INST_SW_BREAKPOINT) {
			run->exit_reason = KVM_EXIT_DEBUG;
			run->debug.arch.address = kvmppc_get_pc(vcpu);
			emulated = EMULATE_EXIT_USER;
			advance = 0;
		} else
			emulated = EMULATE_FAIL;

		break;

	default:
		emulated = EMULATE_FAIL;
	}
