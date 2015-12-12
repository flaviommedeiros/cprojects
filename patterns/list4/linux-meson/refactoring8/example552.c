static struct spi_board_info spi0_board_info[] __initdata = {
#ifdef CONFIG_BOARD_ATSTK1000_EXTDAC
	{
		/* AT73C213 */
		.modalias	= "at73c213",
		.max_speed_hz	= 200000,
		.chip_select	= 0,
		.mode		= SPI_MODE_1,
		.platform_data	= &at73c213_data,
	},
#endif
	/*
	 * We can control the LTV350QV LCD panel, but it isn't much
	 * point since we don't have an LCD controller...
	 */
};
