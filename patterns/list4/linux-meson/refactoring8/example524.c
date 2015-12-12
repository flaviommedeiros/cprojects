static struct i2c_board_info __initdata bfin_i2c_board_info0[] = {
#if defined(CONFIG_SND_SOC_SSM2602) || defined(CONFIG_SND_SOC_SSM2602_MODULE)
	{
		I2C_BOARD_INFO("ssm2602", 0x1b),
	},
#endif
};
