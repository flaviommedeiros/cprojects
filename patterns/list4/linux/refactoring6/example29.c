if (
#ifdef CONFIG_X86_64
		/*
		 * Micro-optimization: the pointer we're following is explicitly
		 * 32 bits, so it can't be out of range.
		 */
		__get_user(*(u32 *)&regs->cx,
			    (u32 __user __force *)(unsigned long)(u32)regs->sp)
#else
		get_user(*(u32 *)&regs->cx,
			 (u32 __user __force *)(unsigned long)(u32)regs->sp)
#endif
		) {

		/* User code screwed up. */
		local_irq_disable();
		regs->ax = -EFAULT;
#ifdef CONFIG_CONTEXT_TRACKING
		enter_from_user_mode();
#endif
		prepare_exit_to_usermode(regs);
		return 0;	/* Keep it simple: use IRET. */
	}
