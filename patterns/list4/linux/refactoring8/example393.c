static struct i2c_board_info __initdata bfin_i2c_board_info[] = {
#if IS_ENABLED(CONFIG_TOUCHSCREEN_AD7160)
	{
		I2C_BOARD_INFO("ad7160", 0x33),
		.irq = IRQ_PH1,
		.platform_data = (void *)&bfin_ad7160_ts_info,
	},
#endif
};
