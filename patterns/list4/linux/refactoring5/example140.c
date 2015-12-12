#ifdef CONFIG_COMPAT
if (is_compat_task())
		ret = compat_setup_rt_frame(ksig, oldset, regs);
	else
#endif
		ret = setup_rt_frame(ksig, oldset, regs);
