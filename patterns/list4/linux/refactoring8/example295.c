static struct i2c_board_info __initdata rx51_peripherals_i2c_board_info_3[] = {
#if defined(CONFIG_SENSORS_LIS3_I2C) || defined(CONFIG_SENSORS_LIS3_I2C_MODULE)
	{
		I2C_BOARD_INFO("lis3lv02d", 0x1d),
		.platform_data = &rx51_lis3lv02d_data,
	},
#endif
};
