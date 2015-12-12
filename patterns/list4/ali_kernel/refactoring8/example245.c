static struct platform_device *tct_hammer_devices[] __initdata = {
	&s3c_device_adc,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_usb,
	&s3c_device_rtc,
	&s3c_device_usbgadget,
	&s3c_device_sdi,
#ifdef CONFIG_MTD_PARTITIONS
	&tct_hammer_device_nor,
#endif
};
