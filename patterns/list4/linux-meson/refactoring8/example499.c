static struct platform_device *m5249_devices[] __initdata = {
#ifdef CONFIG_M5249C3
	&m5249_smc91x,
#endif
};
