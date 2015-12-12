static struct platform_device *smdk2443_devices[] __initdata = {
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_hsmmc1,
#ifdef CONFIG_SND_SOC_SMDK2443_WM9710
	&s3c_device_ac97,
#endif
	&s3c2443_device_dma,
};
