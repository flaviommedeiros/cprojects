static struct platform_device* lpd7a40x_devs[] __initdata = {
	&smc91x_device,
	&lh7a40x_usbclient_device,
#if defined (CONFIG_ARCH_LH7A404)
	&lh7a404_usbhost_device,
#endif
};
