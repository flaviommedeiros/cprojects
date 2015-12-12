static struct spi_board_info u300_spi_devices[] = {
#ifdef CONFIG_MACH_U300_SPIDUMMY
	{
		/* A dummy chip used for loopback tests */
		.modalias       = "spi-dummy",
		/* Really dummy, pass in additional chip config here */
		.platform_data  = NULL,
		/* This defines how the controller shall handle the device */
		.controller_data = &dummy_chip_info,
		/* .irq - no external IRQ routed from this device */
		.max_speed_hz   = 1000000,
		.bus_num        = 0, /* Only one bus on this chip */
		.chip_select    = 0,
		/* Means SPI_CS_HIGH, change if e.g low CS */
		.mode           = 0,
	},
#endif
};
