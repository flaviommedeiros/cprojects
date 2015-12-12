#ifndef CONFIG_SMP
if(last_task_used_math == current) {
#else
	if (test_thread_flag(TIF_USEDFPU)) {
#endif
		/* Clean the fpu. */
		put_psr(get_psr() | PSR_EF);
		fpsave(&current->thread.float_regs[0], &current->thread.fsr,
		       &current->thread.fpqueue[0], &current->thread.fpqdepth);
#ifndef CONFIG_SMP
		last_task_used_math = NULL;
#else
		clear_thread_flag(TIF_USEDFPU);
#endif
	}

	/* Now, this task is no longer a kernel thread. */
	current->thread.current_ds = USER_DS;
	if (current->thread.flags & SPARC_FLAG_KTHREAD) {
		current->thread.flags &= ~SPARC_FLAG_KTHREAD;

		/* We must fixup kregs as well. */
		/* XXX This was not fixed for ti for a while, worked. Unused? */
		current->thread.kregs = (struct pt_regs *)
		    (task_stack_page(current) + (THREAD_SIZE - TRACEREG_SZ));
	}
}
