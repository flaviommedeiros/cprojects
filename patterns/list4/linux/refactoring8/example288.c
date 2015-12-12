static struct sh_mobile_lcdc_info sh_mobile_lcdc_info = {
#if defined(CONFIG_SH_MIGOR_RTA_WVGA)
	.clock_source = LCDC_CLK_BUS,
	.ch[0] = {
		.chan = LCDC_CHAN_MAINLCD,
		.fourcc = V4L2_PIX_FMT_RGB565,
		.interface_type = RGB16,
		.clock_divider = 2,
		.lcd_modes = migor_lcd_modes,
		.num_modes = ARRAY_SIZE(migor_lcd_modes),
		.panel_cfg = { /* 7.0 inch */
			.width = 152,
			.height = 91,
		},
	}
#elif defined(CONFIG_SH_MIGOR_QVGA)
	.clock_source = LCDC_CLK_PERIPHERAL,
	.ch[0] = {
		.chan = LCDC_CHAN_MAINLCD,
		.fourcc = V4L2_PIX_FMT_RGB565,
		.interface_type = SYS16A,
		.clock_divider = 10,
		.lcd_modes = migor_lcd_modes,
		.num_modes = ARRAY_SIZE(migor_lcd_modes),
		.panel_cfg = {
			.width = 49,	/* 2.4 inch */
			.height = 37,
			.setup_sys = migor_lcd_qvga_setup,
		},
		.sys_bus_cfg = {
			.ldmt2r = 0x06000a09,
			.ldmt3r = 0x180e3418,
			/* set 1s delay to encourage fsync() */
			.deferred_io_msec = 1000,
		},
	}
#endif
};
