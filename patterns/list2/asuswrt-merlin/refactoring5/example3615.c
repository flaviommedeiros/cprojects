#ifdef CONFIG_MACH_MX27
if (cpu_is_mx27())
		imx_dmav1_baseaddr = MX27_IO_ADDRESS(MX27_DMA_BASE_ADDR);
	else
#endif
		BUG();
