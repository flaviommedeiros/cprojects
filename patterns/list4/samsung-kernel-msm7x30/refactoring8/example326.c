static struct spi_board_info overo_spi_board_info[] __initdata = {
#if defined(CONFIG_PANEL_LGPHILIPS_LB035Q02) || \
	defined(CONFIG_PANEL_LGPHILIPS_LB035Q02_MODULE)
	{
		.modalias		= "lgphilips_lb035q02_panel-spi",
		.bus_num		= 1,
		.chip_select		= 1,
		.max_speed_hz		= 500000,
		.mode			= SPI_MODE_3,
	},
#endif
};
