static struct platform_device *r7780rp_devices[] __initdata = {
	&r8a66597_usb_host_device,
	&m66592_usb_peripheral_device,
	&heartbeat_device,
	&smbus_device,
	&nor_flash_device,
#ifndef CONFIG_SH_R7780RP
	&ax88796_device,
#endif
};
