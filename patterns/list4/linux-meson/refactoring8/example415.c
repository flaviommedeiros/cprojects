static const struct fb_videomode ap4evb_lcdc_modes[] = {
	{
#ifdef CONFIG_AP4EVB_QHD
		.name		= "R63302(QHD)",
		.xres		= 544,
		.yres		= 961,
		.left_margin	= 72,
		.right_margin	= 600,
		.hsync_len	= 16,
		.upper_margin	= 8,
		.lower_margin	= 8,
		.vsync_len	= 2,
		.sync		= FB_SYNC_VERT_HIGH_ACT | FB_SYNC_HOR_HIGH_ACT,
#else
		.name		= "WVGA Panel",
		.xres		= 800,
		.yres		= 480,
		.left_margin	= 220,
		.right_margin	= 110,
		.hsync_len	= 70,
		.upper_margin	= 20,
		.lower_margin	= 5,
		.vsync_len	= 5,
		.sync		= 0,
#endif
	},
};
