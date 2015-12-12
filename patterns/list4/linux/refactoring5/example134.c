#ifdef CONFIG_ARCH_HAS_SC_SIGNALS
if (!(ksig->ka.sa.sa_flags & SA_SIGINFO))
		err = setup_signal_stack_sc(sp, ksig, regs, oldset);
	else
#endif
		err = setup_signal_stack_si(sp, ksig, regs, oldset);
