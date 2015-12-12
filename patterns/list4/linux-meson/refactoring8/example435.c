static struct spi_board_info usb_a9g20_spi_devices[] = {
#if defined(CONFIG_MMC_SPI) || defined(CONFIG_MMC_SPI_MODULE)
	{
		.modalias = "mmc_spi",
		.max_speed_hz = 20000000,	/* max spi clock (SCK) speed in HZ */
		.bus_num = 1,
		.chip_select = 0,
		.platform_data = &at91_mmc_spi_pdata,
		.mode = SPI_MODE_3,
	},
#endif
};
