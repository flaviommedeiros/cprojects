struct msm_gpiomux_config msm_gpiomux_configs[GPIOMUX_NGPIOS] = {
#ifdef CONFIG_SERIAL_MSM_CONSOLE
	[49] = { /* UART2 RFR */
		.suspended = GPIOMUX_DRV_2MA | GPIOMUX_PULL_DOWN |
			     GPIOMUX_FUNC_2 | GPIOMUX_VALID,
	},
	[50] = { /* UART2 CTS */
		.suspended = GPIOMUX_DRV_2MA | GPIOMUX_PULL_DOWN |
			     GPIOMUX_FUNC_2 | GPIOMUX_VALID,
	},
	[51] = { /* UART2 RX */
		.suspended = GPIOMUX_DRV_2MA | GPIOMUX_PULL_DOWN |
			     GPIOMUX_FUNC_2 | GPIOMUX_VALID,
	},
	[52] = { /* UART2 TX */
		.suspended = GPIOMUX_DRV_2MA | GPIOMUX_PULL_DOWN |
			     GPIOMUX_FUNC_2 | GPIOMUX_VALID,
	},
#endif
};
