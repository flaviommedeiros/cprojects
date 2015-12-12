static struct spi_board_info bfin_spi_board_info[] __initdata = {
#if IS_ENABLED(CONFIG_MMC_SPI)
	{
		.modalias = "mmc_spi",
		.max_speed_hz = 2,
		.bus_num = 1,
		.chip_select = 5,
		.controller_data = &mmc_spi_chip_info,
	},
#endif
};
