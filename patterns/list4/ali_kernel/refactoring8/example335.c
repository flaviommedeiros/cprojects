static struct mci_platform_data __initdata mci0_data = {
	.slot[0] = {
		.bus_width	= 4,
#if defined(CONFIG_BOARD_ATNGW100_EVKLCD10X) || defined(CONFIG_BOARD_ATNGW100_MRMT1)
		.detect_pin     = GPIO_PIN_NONE,
		.wp_pin         = GPIO_PIN_NONE,
#else
		.detect_pin	= GPIO_PIN_PC(25),
		.wp_pin		= GPIO_PIN_PE(0),
#endif
	},
};
