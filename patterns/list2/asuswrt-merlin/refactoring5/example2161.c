#ifdef CONFIG_MACH_MX21
if (cpu_is_mx21())
		imx_dmav1_baseaddr = MX21_IO_ADDRESS(MX21_DMA_BASE_ADDR);
	else
#endif
#ifdef CONFIG_MACH_MX27
	if (cpu_is_mx27())
		imx_dmav1_baseaddr = MX27_IO_ADDRESS(MX27_DMA_BASE_ADDR);
	else
#endif
		BUG();
