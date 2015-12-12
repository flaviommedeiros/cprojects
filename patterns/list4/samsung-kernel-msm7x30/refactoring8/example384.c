static struct i2c_board_info msm_i2c_backlight_info[] = {
	{
#if defined(CONFIG_BACKLIGHT_LM3530)
		I2C_BOARD_INFO("lm3530", 0x38),
		.platform_data = &lm3530_data,
#endif
	}
};
