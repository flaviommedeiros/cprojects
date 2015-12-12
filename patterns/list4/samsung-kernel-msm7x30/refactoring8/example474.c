static struct i2c_board_info i2c_gpio_pmic_devs[] __initdata = {
#if defined(CONFIG_REGULATOR_MAX8998) || defined(CONFIG_REGULATOR_MAX8998_MODULE)
	{
		/* 0xCC when SRAD = 0 */
		I2C_BOARD_INFO("max8998", 0xCC >> 1),
		.platform_data = &aquila_max8998_pdata,
	},
#endif
};
