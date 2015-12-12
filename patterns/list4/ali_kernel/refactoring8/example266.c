static struct spi_board_info __initdata ecb_at91spi_devices[] = {
	{	/* DataFlash chip */
		.modalias	= "mtd_dataflash",
		.chip_select	= 0,
		.max_speed_hz	= 10 * 1000 * 1000,
		.bus_num	= 0,
#if defined(CONFIG_MTD_DATAFLASH)
		.platform_data	= &my_flash0_platform,
#endif
	},
	{	/* User accessable spi - cs1 (250KHz) */
		.modalias	= "spi-cs1",
		.chip_select	= 1,
		.max_speed_hz	= 250 * 1000,
	},
	{	/* User accessable spi - cs2 (1MHz) */
		.modalias	= "spi-cs2",
		.chip_select	= 2,
		.max_speed_hz	= 1 * 1000 * 1000,
	},
	{	/* User accessable spi - cs3 (10MHz) */
		.modalias	= "spi-cs3",
		.chip_select	= 3,
		.max_speed_hz	= 10 * 1000 * 1000,
	},
};
