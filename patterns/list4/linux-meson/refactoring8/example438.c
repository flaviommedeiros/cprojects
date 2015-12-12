static struct spi_board_info ek_spi_devices[] = {
#if defined(CONFIG_RTC_DRV_M41T94)
	{	/* M41T94 RTC */
		.modalias	= "m41t94",
		.chip_select	= 0,
		.max_speed_hz	= 1 * 1000 * 1000,
		.bus_num	= 0,
	}
#endif
};
