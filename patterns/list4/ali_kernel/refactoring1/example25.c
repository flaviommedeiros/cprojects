if (arg == GTP_VAR_COOKED_CLOCK_ID)
			gtp_access_cooked_clock = 1;
#ifdef CONFIG_X86
		else if (arg == GTP_VAR_COOKED_RDTSC_ID)
			gtp_access_cooked_rdtsc = 1;
#endif
