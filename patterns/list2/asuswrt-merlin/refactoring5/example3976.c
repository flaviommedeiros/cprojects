#ifdef RTAC68U
if (cpu_turbo_mode)
	{
		printf("CPU Turbo Mode\n");
		nvstr = strdup("1000,533");
	}
	else
#endif
		nvstr = nvram_safe_get("clkfreq");
