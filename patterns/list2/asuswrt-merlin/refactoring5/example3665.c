#ifdef CONFIG_COMPAT
if (is_compat_task()) {
			ret = handle_signal32(signr, &ka, &info, oldset, regs);
	        }
		else
#endif
			ret = handle_signal(signr, &ka, &info, oldset, regs);
