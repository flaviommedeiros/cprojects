static struct omap_uart_state omap_uart[OMAP_MAX_NR_PORTS] = {
	{
		.pdev = {
			.name			= "serial8250",
			.id			= PLAT8250_DEV_PLATFORM,
			.dev			= {
				.platform_data	= serial_platform_data0,
			},
		},
	}, {
		.pdev = {
			.name			= "serial8250",
			.id			= PLAT8250_DEV_PLATFORM1,
			.dev			= {
				.platform_data	= serial_platform_data1,
			},
		},
	}, {
		.pdev = {
			.name			= "serial8250",
			.id			= PLAT8250_DEV_PLATFORM2,
			.dev			= {
				.platform_data	= serial_platform_data2,
			},
		},
	},
#ifdef CONFIG_ARCH_OMAP4
	{
		.pdev = {
			.name			= "serial8250",
			.id			= 3,
			.dev			= {
				.platform_data	= serial_platform_data3,
			},
		},
	},
#endif
};
