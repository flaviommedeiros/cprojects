#ifdef CONFIG_MACH_MX21
if (cpu_is_mx21())
		audmux_base = MX21_IO_ADDRESS(MX21_AUDMUX_BASE_ADDR);
	else
#endif
#ifdef CONFIG_MACH_MX27
	if (cpu_is_mx27())
		audmux_base = MX27_IO_ADDRESS(MX27_AUDMUX_BASE_ADDR);
	else
#endif
		(void)0;
