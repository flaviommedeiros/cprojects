static struct msm_gpiomux_config msm8x60_uart_configs[] __initdata = {
	{ /* UARTDM_TX */
		.gpio      = 53,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart1dm_active,
			[GPIOMUX_SUSPENDED] = &uart1dm_suspended,
		},
	},
	{ /* UARTDM_RX */
		.gpio      = 54,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart1dm_active,
			[GPIOMUX_SUSPENDED] = &uart1dm_suspended,
		},
	},
	{ /* UARTDM_CTS */
		.gpio      = 55,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart1dm_active,
			[GPIOMUX_SUSPENDED] = &uart1dm_suspended,
		},
	},
	{ /* UARTDM_RFR */
		.gpio      = 56,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart1dm_active,
			[GPIOMUX_SUSPENDED] = &uart1dm_suspended,
		},
	},
	{
		.gpio      = 115,
		.settings = {
			[GPIOMUX_SUSPENDED] = &console_uart,
		},
	},
	{
		.gpio      = 116,
		.settings = {
			[GPIOMUX_SUSPENDED] = &console_uart,
		},
	},
#if !defined(CONFIG_USB_PEHCI_HCD) && !defined(CONFIG_USB_PEHCI_HCD_MODULE)
	/* USB ISP1763 may also use 117 GPIO */
	{
		.gpio      = 117,
		.settings = {
			[GPIOMUX_SUSPENDED] = &console_uart,
		},
	},
#endif
	{
		.gpio      = 118,
		.settings = {
			[GPIOMUX_SUSPENDED] = &console_uart,
		},
	},
};
