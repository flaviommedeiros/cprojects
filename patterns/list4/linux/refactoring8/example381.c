static struct i2c_board_info __initdata bfin_i2c_board_info0[] = {
#if IS_ENABLED(CONFIG_SND_SOC_SSM2602)
	{
		I2C_BOARD_INFO("ssm2602", 0x1b),
	},
#endif
};
