static struct platform_device *amlm5900_devices[] __initdata = {
#ifdef CONFIG_FB_S3C2410
	&s3c_device_lcd,
#endif
	&s3c_device_adc,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_ohci,
 	&s3c_device_rtc,
	&s3c_device_usbgadget,
        &s3c_device_sdi,
	&amlm5900_device_nor,
};
