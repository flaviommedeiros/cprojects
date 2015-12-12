static const struct lcd_ctrl *ctrls[] = {
	&omap1_int_ctrl,

#ifdef CONFIG_FB_OMAP_LCDC_HWA742
	&hwa742_ctrl,
#endif
};
