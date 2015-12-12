static struct omap_dss_device *overo_dss_devices[] = {
	&overo_dvi_device,
	&overo_tv_device,
#if defined(CONFIG_PANEL_LGPHILIPS_LB035Q02) || \
	defined(CONFIG_PANEL_LGPHILIPS_LB035Q02_MODULE)
	&overo_lcd35_device,
#endif
	&overo_lcd43_device,
};
