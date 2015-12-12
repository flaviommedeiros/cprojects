static struct platform_device *sh7750_devices[] __initdata = {
	&rtc_device,
	&tmu0_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7750R) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751R)
	&tmu1_device,
#endif
};
