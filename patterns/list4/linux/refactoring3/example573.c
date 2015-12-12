switch (fault_num) {
	case INT_MEM_ERROR:
		signo = SIGBUS;
		code = BUS_OBJERR;
		break;
	case INT_ILL:
		if (copy_from_user(&instr, (void __user *)regs->pc,
				   sizeof(instr))) {
			pr_err("Unreadable instruction for INT_ILL: %#lx\n",
			       regs->pc);
			do_exit(SIGKILL);
		}
		if (!special_ill(instr, &signo, &code)) {
			signo = SIGILL;
			code = ILL_ILLOPC;
		}
		address = regs->pc;
		break;
	case INT_GPV:
#if CHIP_HAS_TILE_DMA()
		if (retry_gpv(reason))
			goto done;
#endif
		/*FALLTHROUGH*/
	case INT_UDN_ACCESS:
	case INT_IDN_ACCESS:
#if CHIP_HAS_SN()
	case INT_SN_ACCESS:
#endif
		signo = SIGILL;
		code = ILL_PRVREG;
		address = regs->pc;
		break;
	case INT_SWINT_3:
	case INT_SWINT_2:
	case INT_SWINT_0:
		signo = SIGILL;
		code = ILL_ILLTRP;
		address = regs->pc;
		break;
	case INT_UNALIGN_DATA:
#ifndef __tilegx__  /* Emulated support for single step debugging */
		if (unaligned_fixup >= 0) {
			struct single_step_state *state =
				current_thread_info()->step_state;
			if (!state ||
			    (void __user *)(regs->pc) != state->buffer) {
				single_step_once(regs);
				goto done;
			}
		}
#endif
		signo = SIGBUS;
		code = BUS_ADRALN;
		address = 0;
		break;
	case INT_DOUBLE_FAULT:
		/*
		 * For double fault, "reason" is actually passed as
		 * SYSTEM_SAVE_K_2, the hypervisor's double-fault info, so
		 * we can provide the original fault number rather than
		 * the uninteresting "INT_DOUBLE_FAULT" so the user can
		 * learn what actually struck while PL0 ICS was set.
		 */
		fault_num = reason;
		signo = SIGILL;
		code = ILL_DBLFLT;
		address = regs->pc;
		break;
#ifdef __tilegx__
	case INT_ILL_TRANS: {
		/* Avoid a hardware erratum with the return address stack. */
		fill_ra_stack();

		signo = SIGSEGV;
		address = reason;
		code = SEGV_MAPERR;
		break;
	}
#endif
	default:
		panic("Unexpected do_trap interrupt number %d", fault_num);
	}
