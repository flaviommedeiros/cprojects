#ifdef CONFIG_IA32_EMULATION
if (is_ia32_task())
			err = do_set_thread_area(p, -1,
				(struct user_desc __user *)tls, 0);
		else
#endif
			err = do_arch_prctl(p, ARCH_SET_FS, tls);
