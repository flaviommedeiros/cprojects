static struct plat_sci_port sci_platform_data[] = {
	{
#ifndef CONFIG_SH_RTS7751R2D
		.mapbase	= 0xffe00000,
		.flags		= UPF_BOOT_AUTOCONF,
		.type		= PORT_SCI,
		.irqs		= { 23, 23, 23, 0 },
	}, {
#endif
		.mapbase	= 0xffe80000,
		.flags		= UPF_BOOT_AUTOCONF,
		.type		= PORT_SCIF,
		.irqs		= { 40, 40, 40, 40 },
	}, {
		.flags = 0,
	}
};
