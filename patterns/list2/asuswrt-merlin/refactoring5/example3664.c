#ifdef CONFIG_MATHEMU
if (signal == SIGFPE)
		do_fp_trap(regs, location,
                           current->thread.fp_regs.fpc, interruption_code);
        else if (signal == SIGSEGV) {
		info.si_signo = signal;
		info.si_errno = 0;
		info.si_code = SEGV_MAPERR;
		info.si_addr = (void __user *) location;
		do_trap(interruption_code, signal,
			"user address fault", regs, &info);
	} else
#endif
        if (signal) {
		info.si_signo = signal;
		info.si_errno = 0;
		info.si_code = ILL_ILLOPC;
		info.si_addr = (void __user *) location;
		do_trap(interruption_code, signal,
			"illegal operation", regs, &info);
	}
