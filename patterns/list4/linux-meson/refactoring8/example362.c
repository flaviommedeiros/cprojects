static struct platform_device *sh7750_devices[] __initdata = {
	&rtc_device,
	&tmu0_device,
	&tmu1_device,
	&tmu2_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7750R) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751) || \
	defined(CONFIG_CPU_SUBTYPE_SH7751R)
	&tmu3_device,
	&tmu4_device,
#endif
};
