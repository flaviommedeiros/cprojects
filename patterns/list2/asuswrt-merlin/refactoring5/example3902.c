#ifdef CONFIG_64BIT
if (is_compat_task()) {
		DBG(1,"sys_rt_sigreturn: compat_frame->uc.uc_mcontext 0x%p\n",
				&compat_frame->uc.uc_mcontext);
		if (restore_sigcontext32(&compat_frame->uc.uc_mcontext, 
					&compat_frame->regs, regs))
			goto give_sigsegv;
		DBG(1,"sys_rt_sigreturn: usp %#08lx stack 0x%p\n", 
				usp, &compat_frame->uc.uc_stack);
		if (do_sigaltstack32(&compat_frame->uc.uc_stack, NULL, usp) == -EFAULT)
			goto give_sigsegv;
	} else
#endif
	{
		DBG(1,"sys_rt_sigreturn: frame->uc.uc_mcontext 0x%p\n",
				&frame->uc.uc_mcontext);
		if (restore_sigcontext(&frame->uc.uc_mcontext, regs))
			goto give_sigsegv;
		DBG(1,"sys_rt_sigreturn: usp %#08lx stack 0x%p\n", 
				usp, &frame->uc.uc_stack);
		if (do_sigaltstack(&frame->uc.uc_stack, NULL, usp) == -EFAULT)
			goto give_sigsegv;
	}
