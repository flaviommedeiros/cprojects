static struct spi_board_info dk_spi_devices[] = {
	{	/* DataFlash chip */
		.modalias	= "mtd_dataflash",
		.chip_select	= 0,
		.max_speed_hz	= 15 * 1000 * 1000,
	},
	{	/* UR6HCPS2-SP40 PS2-to-SPI adapter */
		.modalias	= "ur6hcps2",
		.chip_select	= 1,
		.max_speed_hz	= 250 *  1000,
	},
	{	/* TLV1504 ADC, 4 channels, 10 bits; one is a temp sensor */
		.modalias	= "tlv1504",
		.chip_select	= 2,
		.max_speed_hz	= 20 * 1000 * 1000,
	},
#ifdef CONFIG_MTD_AT91_DATAFLASH_CARD
	{	/* DataFlash card */
		.modalias	= "mtd_dataflash",
		.chip_select	= 3,
		.max_speed_hz	= 15 * 1000 * 1000,
	}
#endif
};
