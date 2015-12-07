#ifdef CONFIG_IA32_EMULATION
if (test_thread_flag(TIF_IA32)) {
		if (ka->sa.sa_flags & SA_SIGINFO)
			ret = ia32_setup_rt_frame(sig, ka, info, oldset, regs);
		else
			ret = ia32_setup_frame(sig, ka, oldset, regs);
	} else 
#endif
	ret = setup_rt_frame(sig, ka, info, oldset, regs);
