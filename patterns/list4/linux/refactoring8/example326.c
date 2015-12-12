static struct omap_usb_config osk_usb_config __initdata = {
	/* has usb host connector (A) ... for development it can also
	 * be used, with a NONSTANDARD gender-bending cable/dongle, as
	 * a peripheral.
	 */
#if IS_ENABLED(CONFIG_USB_OMAP)
	.register_dev	= 1,
	.hmc_mode	= 0,
#else
	.register_host	= 1,
	.hmc_mode	= 16,
	.rwc		= 1,
#endif
	.pins[0]	= 2,
};
