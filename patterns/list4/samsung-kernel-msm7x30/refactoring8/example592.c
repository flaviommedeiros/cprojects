static struct mci_platform_data __initdata mci0_data = {
	.slot[0] = {
		.bus_width	= 4,

/* MMC card detect requires MACB0 *NOT* be used */
#ifdef CONFIG_BOARD_ATSTK1002_SW6_CUSTOM
		.detect_pin	= GPIO_PIN_PC(14), /* gpio30/sdcd */
		.wp_pin		= GPIO_PIN_PC(15), /* gpio31/sdwp */
#else
		.detect_pin	= -ENODEV,
		.wp_pin		= -ENODEV,
#endif	/* SW6 for sd{cd,wp} routing */
	},
};
