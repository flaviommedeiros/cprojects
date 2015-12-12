static struct i2c_board_info __initdata bfin_i2c_board_info[] = {
#if defined(CONFIG_TOUCHSCREEN_AD7160) || defined(CONFIG_TOUCHSCREEN_AD7160_MODULE)
	{
		I2C_BOARD_INFO("ad7160", 0x33),
		.irq = IRQ_PH1,
		.platform_data = (void *)&bfin_ad7160_ts_info,
	},
#endif
};
