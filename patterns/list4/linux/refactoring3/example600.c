switch (insn.i_format.opcode) {
		/*
		 * These are instructions that a compiler doesn't generate.  We
		 * can assume therefore that the code is MIPS-aware and
		 * really buggy.  Emulating these instructions would break the
		 * semantics anyway.
		 */
	case ll_op:
	case lld_op:
	case sc_op:
	case scd_op:

		/*
		 * For these instructions the only way to create an address
		 * error is an attempted access to kernel/supervisor address
		 * space.
		 */
	case ldl_op:
	case ldr_op:
	case lwl_op:
	case lwr_op:
	case sdl_op:
	case sdr_op:
	case swl_op:
	case swr_op:
	case lb_op:
	case lbu_op:
	case sb_op:
		goto sigbus;

		/*
		 * The remaining opcodes are the ones that are really of
		 * interest.
		 */
#ifdef CONFIG_EVA
	case spec3_op:
		/*
		 * we can land here only from kernel accessing user memory,
		 * so we need to "switch" the address limit to user space, so
		 * address check can work properly.
		 */
		seg = get_fs();
		set_fs(USER_DS);
		switch (insn.spec3_format.func) {
		case lhe_op:
			if (!access_ok(VERIFY_READ, addr, 2)) {
				set_fs(seg);
				goto sigbus;
			}
			LoadHWE(addr, value, res);
			if (res) {
				set_fs(seg);
				goto fault;
			}
			compute_return_epc(regs);
			regs->regs[insn.spec3_format.rt] = value;
			break;
		case lwe_op:
			if (!access_ok(VERIFY_READ, addr, 4)) {
				set_fs(seg);
				goto sigbus;
			}
				LoadWE(addr, value, res);
			if (res) {
				set_fs(seg);
				goto fault;
			}
			compute_return_epc(regs);
			regs->regs[insn.spec3_format.rt] = value;
			break;
		case lhue_op:
			if (!access_ok(VERIFY_READ, addr, 2)) {
				set_fs(seg);
				goto sigbus;
			}
			LoadHWUE(addr, value, res);
			if (res) {
				set_fs(seg);
				goto fault;
			}
			compute_return_epc(regs);
			regs->regs[insn.spec3_format.rt] = value;
			break;
		case she_op:
			if (!access_ok(VERIFY_WRITE, addr, 2)) {
				set_fs(seg);
				goto sigbus;
			}
			compute_return_epc(regs);
			value = regs->regs[insn.spec3_format.rt];
			StoreHWE(addr, value, res);
			if (res) {
				set_fs(seg);
				goto fault;
			}
			break;
		case swe_op:
			if (!access_ok(VERIFY_WRITE, addr, 4)) {
				set_fs(seg);
				goto sigbus;
			}
			compute_return_epc(regs);
			value = regs->regs[insn.spec3_format.rt];
			StoreWE(addr, value, res);
			if (res) {
				set_fs(seg);
				goto fault;
			}
			break;
		default:
			set_fs(seg);
			goto sigill;
		}
		set_fs(seg);
		break;
#endif
	case lh_op:
		if (!access_ok(VERIFY_READ, addr, 2))
			goto sigbus;

		if (config_enabled(CONFIG_EVA)) {
			if (segment_eq(get_fs(), get_ds()))
				LoadHW(addr, value, res);
			else
				LoadHWE(addr, value, res);
		} else {
			LoadHW(addr, value, res);
		}

		if (res)
			goto fault;
		compute_return_epc(regs);
		regs->regs[insn.i_format.rt] = value;
		break;

	case lw_op:
		if (!access_ok(VERIFY_READ, addr, 4))
			goto sigbus;

		if (config_enabled(CONFIG_EVA)) {
			if (segment_eq(get_fs(), get_ds()))
				LoadW(addr, value, res);
			else
				LoadWE(addr, value, res);
		} else {
			LoadW(addr, value, res);
		}

		if (res)
			goto fault;
		compute_return_epc(regs);
		regs->regs[insn.i_format.rt] = value;
		break;

	case lhu_op:
		if (!access_ok(VERIFY_READ, addr, 2))
			goto sigbus;

		if (config_enabled(CONFIG_EVA)) {
			if (segment_eq(get_fs(), get_ds()))
				LoadHWU(addr, value, res);
			else
				LoadHWUE(addr, value, res);
		} else {
			LoadHWU(addr, value, res);
		}

		if (res)
			goto fault;
		compute_return_epc(regs);
		regs->regs[insn.i_format.rt] = value;
		break;

	case lwu_op:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * if we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit instruction here the sdl/sdr
		 * would blow up, so for now we don't handle unaligned 64-bit
		 * instructions on 32-bit kernels.
		 */
		if (!access_ok(VERIFY_READ, addr, 4))
			goto sigbus;

		LoadWU(addr, value, res);
		if (res)
			goto fault;
		compute_return_epc(regs);
		regs->regs[insn.i_format.rt] = value;
		break;
#endif /* CONFIG_64BIT */

		/* Cannot handle 64-bit instructions in 32-bit kernel */
		goto sigill;

	case ld_op:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * if we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit instruction here the sdl/sdr
		 * would blow up, so for now we don't handle unaligned 64-bit
		 * instructions on 32-bit kernels.
		 */
		if (!access_ok(VERIFY_READ, addr, 8))
			goto sigbus;

		LoadDW(addr, value, res);
		if (res)
			goto fault;
		compute_return_epc(regs);
		regs->regs[insn.i_format.rt] = value;
		break;
#endif /* CONFIG_64BIT */

		/* Cannot handle 64-bit instructions in 32-bit kernel */
		goto sigill;

	case sh_op:
		if (!access_ok(VERIFY_WRITE, addr, 2))
			goto sigbus;

		compute_return_epc(regs);
		value = regs->regs[insn.i_format.rt];

		if (config_enabled(CONFIG_EVA)) {
			if (segment_eq(get_fs(), get_ds()))
				StoreHW(addr, value, res);
			else
				StoreHWE(addr, value, res);
		} else {
			StoreHW(addr, value, res);
		}

		if (res)
			goto fault;
		break;

	case sw_op:
		if (!access_ok(VERIFY_WRITE, addr, 4))
			goto sigbus;

		compute_return_epc(regs);
		value = regs->regs[insn.i_format.rt];

		if (config_enabled(CONFIG_EVA)) {
			if (segment_eq(get_fs(), get_ds()))
				StoreW(addr, value, res);
			else
				StoreWE(addr, value, res);
		} else {
			StoreW(addr, value, res);
		}

		if (res)
			goto fault;
		break;

	case sd_op:
#ifdef CONFIG_64BIT
		/*
		 * A 32-bit kernel might be running on a 64-bit processor.  But
		 * if we're on a 32-bit processor and an i-cache incoherency
		 * or race makes us see a 64-bit instruction here the sdl/sdr
		 * would blow up, so for now we don't handle unaligned 64-bit
		 * instructions on 32-bit kernels.
		 */
		if (!access_ok(VERIFY_WRITE, addr, 8))
			goto sigbus;

		compute_return_epc(regs);
		value = regs->regs[insn.i_format.rt];
		StoreDW(addr, value, res);
		if (res)
			goto fault;
		break;
#endif /* CONFIG_64BIT */

		/* Cannot handle 64-bit instructions in 32-bit kernel */
		goto sigill;

	case lwc1_op:
	case ldc1_op:
	case swc1_op:
	case sdc1_op:
		die_if_kernel("Unaligned FP access in kernel code", regs);
		BUG_ON(!used_math());

		lose_fpu(1);	/* Save FPU state for the emulator. */
		res = fpu_emulator_cop1Handler(regs, &current->thread.fpu, 1,
					       &fault_addr);
		own_fpu(1);	/* Restore FPU state. */

		/* Signal if something went wrong. */
		process_fpemu_return(res, fault_addr, 0);

		if (res == 0)
			break;
		return;

	case msa_op:
		if (!cpu_has_msa)
			goto sigill;

		/*
		 * If we've reached this point then userland should have taken
		 * the MSA disabled exception & initialised vector context at
		 * some point in the past.
		 */
		BUG_ON(!thread_msa_context_live());

		df = insn.msa_mi10_format.df;
		wd = insn.msa_mi10_format.wd;
		fpr = &current->thread.fpu.fpr[wd];

		switch (insn.msa_mi10_format.func) {
		case msa_ld_op:
			if (!access_ok(VERIFY_READ, addr, sizeof(*fpr)))
				goto sigbus;

			/*
			 * Disable preemption to avoid a race between copying
			 * state from userland, migrating to another CPU and
			 * updating the hardware vector register below.
			 */
			preempt_disable();

			res = __copy_from_user_inatomic(fpr, addr,
							sizeof(*fpr));
			if (res)
				goto fault;

			/*
			 * Update the hardware register if it is in use by the
			 * task in this quantum, in order to avoid having to
			 * save & restore the whole vector context.
			 */
			if (test_thread_flag(TIF_USEDMSA))
				write_msa_wr(wd, fpr, df);

			preempt_enable();
			break;

		case msa_st_op:
			if (!access_ok(VERIFY_WRITE, addr, sizeof(*fpr)))
				goto sigbus;

			/*
			 * Update from the hardware register if it is in use by
			 * the task in this quantum, in order to avoid having to
			 * save & restore the whole vector context.
			 */
			preempt_disable();
			if (test_thread_flag(TIF_USEDMSA))
				read_msa_wr(wd, fpr, df);
			preempt_enable();

			res = __copy_to_user_inatomic(addr, fpr, sizeof(*fpr));
			if (res)
				goto fault;
			break;

		default:
			goto sigbus;
		}

		compute_return_epc(regs);
		break;

#ifndef CONFIG_CPU_MIPSR6
	/*
	 * COP2 is available to implementor for application specific use.
	 * It's up to applications to register a notifier chain and do
	 * whatever they have to do, including possible sending of signals.
	 *
	 * This instruction has been reallocated in Release 6
	 */
	case lwc2_op:
		cu2_notifier_call_chain(CU2_LWC2_OP, regs);
		break;

	case ldc2_op:
		cu2_notifier_call_chain(CU2_LDC2_OP, regs);
		break;

	case swc2_op:
		cu2_notifier_call_chain(CU2_SWC2_OP, regs);
		break;

	case sdc2_op:
		cu2_notifier_call_chain(CU2_SDC2_OP, regs);
		break;
#endif
	default:
		/*
		 * Pheeee...  We encountered an yet unknown instruction or
		 * cache coherence problem.  Die sucker, die ...
		 */
		goto sigill;
	}
