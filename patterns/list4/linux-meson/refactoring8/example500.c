static struct platform_device *m5441x_devices[] __initdata = {
#if IS_ENABLED(CONFIG_RTC_DRV_M5441x)
	&m5441x_rtc,
#endif
};
