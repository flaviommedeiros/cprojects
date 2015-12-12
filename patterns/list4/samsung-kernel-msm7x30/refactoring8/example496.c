static struct i2c_board_info __initdata bus0_i2c_board_info[] = {
#ifdef CONFIG_AB3100_CORE
	{
		.type = "ab3100",
		.addr = 0x48,
		.irq = IRQ_U300_IRQ0_EXT,
		.platform_data = &ab3100_plf_data,
	},
#else
	{ },
#endif
};
