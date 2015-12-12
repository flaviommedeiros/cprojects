static struct spi_board_info foxg20_spi_devices[] = {
#if !IS_ENABLED(CONFIG_MMC_ATMELMCI)
	{
		.modalias	= "mtd_dataflash",
		.chip_select	= 1,
		.max_speed_hz	= 15 * 1000 * 1000,
		.bus_num	= 0,
	},
#endif
};
