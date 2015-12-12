static const struct fb_videomode migor_lcd_modes[] = {
	{
#if defined(CONFIG_SH_MIGOR_RTA_WVGA)
		.name = "LB070WV1",
		.xres = 800,
		.yres = 480,
		.left_margin = 64,
		.right_margin = 16,
		.hsync_len = 120,
		.sync = 0,
#elif defined(CONFIG_SH_MIGOR_QVGA)
		.name = "PH240320T",
		.xres = 320,
		.yres = 240,
		.left_margin = 0,
		.right_margin = 16,
		.hsync_len = 8,
		.sync = FB_SYNC_HOR_HIGH_ACT,
#endif
		.upper_margin = 1,
		.lower_margin = 17,
		.vsync_len = 2,
	},
};
