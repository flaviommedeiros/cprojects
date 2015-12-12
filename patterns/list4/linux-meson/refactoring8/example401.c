static struct platform_device *devices[] __initdata = {
	&msm_device_gpio_7x30,
#if defined(CONFIG_SERIAL_MSM) || defined(CONFIG_MSM_SERIAL_DEBUGGER)
        &msm_device_uart2,
#endif
	&msm_device_smd,
	&msm_device_otg,
	&msm_device_hsusb,
	&msm_device_hsusb_host,
};
