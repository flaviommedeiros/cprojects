static struct resource viper_serial_resources[] = {
#ifndef CONFIG_SERIAL_PXA
	{
		.start	= 0x40100000,
		.end	= 0x4010001f,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= 0x40200000,
		.end	= 0x4020001f,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= 0x40700000,
		.end	= 0x4070001f,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= VIPER_UARTA_PHYS,
		.end	= VIPER_UARTA_PHYS + 0xf,
		.flags	= IORESOURCE_MEM,
	},
	{
		.start	= VIPER_UARTB_PHYS,
		.end	= VIPER_UARTB_PHYS + 0xf,
		.flags	= IORESOURCE_MEM,
	},
#else
	{
		0,
	},
#endif
};
