static struct i2c_board_info __initdata bfin_i2c_board_info[] = {
#if defined(CONFIG_FB_BFIN_7393) || defined(CONFIG_FB_BFIN_7393_MODULE)
	{
		I2C_BOARD_INFO("bfin-adv7393", 0x2B),
	},
#endif
};
