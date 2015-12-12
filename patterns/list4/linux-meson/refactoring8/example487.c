static struct i2c_board_info __initdata mx31ads_i2c1_devices[] = {
#ifdef CONFIG_MACH_MX31ADS_WM1133_EV1
	{
		I2C_BOARD_INFO("wm8350", 0x1a),
		.platform_data = &mx31_wm8350_pdata,
		/* irq number is run-time assigned */
	},
#endif
};
