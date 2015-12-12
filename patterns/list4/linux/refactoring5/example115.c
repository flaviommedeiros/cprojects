#ifdef CONFIG_MATH_EMULATION
if (!cpu_has_fpu)
		fpstate_init_soft(&current->thread.fpu.state.soft);
	else
#endif
		asm volatile ("fninit");
