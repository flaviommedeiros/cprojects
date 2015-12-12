static struct i2c_board_info __initdata i2c_info[] = {
	{I2C_BOARD_INFO("camblock", 0x43)},
	{I2C_BOARD_INFO("tmp100", 0x48)},
	{I2C_BOARD_INFO("tmp100", 0x4A)},
	{I2C_BOARD_INFO("tmp100", 0x4C)},
	{I2C_BOARD_INFO("tmp100", 0x4D)},
	{I2C_BOARD_INFO("tmp100", 0x4E)},
#ifdef CONFIG_RTC_DRV_PCF8563
	{I2C_BOARD_INFO("pcf8563", 0x51)},
#endif
	{I2C_BOARD_INFO("pca9536", 0x41)},
	{I2C_BOARD_INFO("fnp300", 0x40)},
	{I2C_BOARD_INFO("fnp300", 0x42)},
	{I2C_BOARD_INFO("adc101", 0x54)},
};
