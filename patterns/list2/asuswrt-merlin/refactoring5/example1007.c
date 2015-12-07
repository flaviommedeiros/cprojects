#ifdef CONFIG_ARCH_HAS_SC_SIGNALS
if(!(ka->sa.sa_flags & SA_SIGINFO))
		err = setup_signal_stack_sc(sp, signr, ka, regs, oldset);
	else
#endif
		err = setup_signal_stack_si(sp, signr, ka, regs, info, oldset);
