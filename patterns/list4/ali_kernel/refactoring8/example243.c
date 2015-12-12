static struct resource smc91x_resources[] = {
	[0] = {
		.start	= PLEB_ETH0_P,
		.end	= PLEB_ETH0_P | 0x03ffffff,
		.flags	= IORESOURCE_MEM,
	},
#if 0 /* Autoprobe instead, to get rising/falling edge characteristic right */
	[1] = {
		.start	= IRQ_GPIO_ETH0_IRQ,
		.end	= IRQ_GPIO_ETH0_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
#endif
};
