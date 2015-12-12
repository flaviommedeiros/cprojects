static struct platform_device *sh7750_early_devices[] __initdata = {
	&tmu0_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7750R) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751R)
	&tmu1_device,
#endif
};
