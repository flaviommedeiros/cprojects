static struct usbhs_omap_platform_data usbhs_bdata __initdata = {
	.port_mode[0] = OMAP_EHCI_PORT_MODE_PHY,
#if defined(CONFIG_PANEL_SHARP_LQ043T1DG01) || \
		defined(CONFIG_PANEL_SHARP_LQ043T1DG01_MODULE)
	.port_mode[1] = OMAP_USBHS_PORT_MODE_UNUSED,
#else
	.port_mode[1] = OMAP_EHCI_PORT_MODE_PHY,
#endif
};
