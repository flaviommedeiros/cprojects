static struct i2c_board_info __initdata bfin_i2c_board_info[] = {
#if IS_ENABLED(CONFIG_FB_BFIN_7393)
	{
		I2C_BOARD_INFO("bfin-adv7393", 0x2B),
	},
#endif
};
