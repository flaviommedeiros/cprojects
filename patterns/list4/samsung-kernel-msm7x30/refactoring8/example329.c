static struct omap_usb_config sdp2430_usb_config __initdata = {
	.otg		= 1,
#ifdef  CONFIG_USB_GADGET_OMAP
	.hmc_mode	= 0x0,
#elif   defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
	.hmc_mode	= 0x1,
#endif
	.pins[0]	= 3,
};
