#ifdef CONFIG_64BIT
if (is_compat_task()) {
		regs->gr[25] = A(&compat_frame->info); /* siginfo pointer */
		regs->gr[24] = A(&compat_frame->uc);   /* ucontext pointer */
	} else
#endif
	{		
		regs->gr[25] = A(&frame->info); /* siginfo pointer */
		regs->gr[24] = A(&frame->uc);   /* ucontext pointer */
	}
