static struct i2c_board_info __initdata bus1_i2c_board_info[] = {
#ifdef CONFIG_MACH_U300_BS335
	{
		.type = "fwcam",
		.addr = 0x10,
	},
	{
		.type = "fwcam",
		.addr = 0x5d,
	},
#else
	{ },
#endif
};
