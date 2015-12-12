static struct platform_device *se_devices[] __initdata = {
	&heartbeat_device,
	&cf_ide_device,
#if defined(CONFIG_CPU_SUBTYPE_SH7710) ||\
	defined(CONFIG_CPU_SUBTYPE_SH7712)
	&sh_eth0_device,
	&sh_eth1_device,
#endif
};
