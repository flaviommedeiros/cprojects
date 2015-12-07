#ifdef CONFIG_ARCH_MX1
if (cpu_is_mx1()) {
		imx_iomuxv1_baseaddr = MX1_IO_ADDRESS(MX1_GPIO_BASE_ADDR);
		imx_iomuxv1_numports = MX1_NUM_GPIO_PORT;
	} else
#endif
#ifdef CONFIG_MACH_MX21
	if (cpu_is_mx21()) {
		imx_iomuxv1_baseaddr = MX21_IO_ADDRESS(MX21_GPIO_BASE_ADDR);
		imx_iomuxv1_numports = MX21_NUM_GPIO_PORT;
	} else
#endif
#ifdef CONFIG_MACH_MX27
	if (cpu_is_mx27()) {
		imx_iomuxv1_baseaddr = MX27_IO_ADDRESS(MX27_GPIO_BASE_ADDR);
		imx_iomuxv1_numports = MX27_NUM_GPIO_PORT;
	} else
#endif
		return -ENODEV;
