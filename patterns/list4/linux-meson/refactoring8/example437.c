static struct spi_board_info yl9200_spi_devices[] = {
#if defined(CONFIG_TOUCHSCREEN_ADS7846) || defined(CONFIG_TOUCHSCREEN_ADS7846_MODULE)
	{	/* Touchscreen */
		.modalias	= "ads7846",
		.chip_select	= 0,
		.max_speed_hz	= 5000 * 26,
		.platform_data	= &ads_info,
		.irq		= AT91_PIN_PB11,
	},
#endif
	{	/* CAN */
		.modalias	= "mcp2510",
		.chip_select	= 1,
		.max_speed_hz	= 25000 * 26,
		.irq		= AT91_PIN_PC0,
	}
};
