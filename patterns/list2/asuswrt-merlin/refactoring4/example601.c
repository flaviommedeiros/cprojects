#if defined(RTAC68U) || defined(DSLAC68U)
if ((si_gpioin(sih) & gpiomask))
#else
	if (!(si_gpioin(sih) & gpiomask))
#endif
		cpu_turbo_mode = 1;
