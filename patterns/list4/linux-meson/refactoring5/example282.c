#ifndef CONFIG_SMP
if(last_task_used_math == current) {
#else
	if (test_thread_flag(TIF_USEDFPU)) {
#endif
		/* Keep process from leaving FPU in a bogon state. */
		put_psr(get_psr() | PSR_EF);
		fpsave(&current->thread.float_regs[0], &current->thread.fsr,
		       &current->thread.fpqueue[0], &current->thread.fpqdepth);
#ifndef CONFIG_SMP
		last_task_used_math = NULL;
#else
		clear_thread_flag(TIF_USEDFPU);
#endif
	}
}
