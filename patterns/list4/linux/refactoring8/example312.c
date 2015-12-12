static unsigned long pcm027_pin_config[] __initdata = {
	/* Chip Selects */
	GPIO20_nSDCS_2,
	GPIO21_nSDCS_3,
	GPIO15_nCS_1,
	GPIO78_nCS_2,
	GPIO80_nCS_4,
	GPIO33_nCS_5,	/* Ethernet */

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* GPIO */
	GPIO52_GPIO,	/* IRQ from network controller */
#ifdef CONFIG_LEDS_GPIO
	GPIO90_GPIO,	/* PCM027_LED_CPU */
	GPIO91_GPIO,	/* PCM027_LED_HEART_BEAT */
#endif
	GPIO114_GPIO,	/* IRQ from CAN controller */
};
