#ifdef CONFIG_MATHEMU
if (signal == SIGFPE)
		do_fp_trap(regs, current->thread.fp_regs.fpc);
	else if (signal == SIGSEGV)
		do_trap(regs, signal, SEGV_MAPERR, "user address fault");
	else
#endif
	if (signal)
		do_trap(regs, signal, ILL_ILLOPC, "illegal operation");
