static struct platform_device *misc_devices[] __initdata = {
#ifdef CONFIG_ANDROID_VIBRATOR
	&android_vibrator_device,
#endif
};
