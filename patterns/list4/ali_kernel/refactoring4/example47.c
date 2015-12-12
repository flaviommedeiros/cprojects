#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,25))
if (regs->flags & X86_EFLAGS_IF)
		#else
		if (regs->eflags & X86_EFLAGS_IF)
		#endif
			__get_cpu_var(gtp_step).irq_need_open = 1;
		else
			__get_cpu_var(gtp_step).irq_need_open = 0;
