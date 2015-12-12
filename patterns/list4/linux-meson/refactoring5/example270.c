#ifdef CONFIG_IA32_EMULATION
if (test_thread_flag(TIF_IA32))
			err = do_set_thread_area(p, -1,
				(struct user_desc __user *)childregs->si, 0);
		else
#endif
			err = do_arch_prctl(p, ARCH_SET_FS, childregs->r8);
