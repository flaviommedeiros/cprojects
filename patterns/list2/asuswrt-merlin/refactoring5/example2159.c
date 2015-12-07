#ifdef CONFIG_MACH_MX27
if (cpu_is_mx27())
		audmux_base = MX27_IO_ADDRESS(MX27_AUDMUX_BASE_ADDR);
	else
#endif
		(void)0;
