static struct platform_device *msm_host_devices[] = {
	&msm_device_hsusb_host,
#ifdef CONFIG_USB_FS_HOST
	&msm_device_hsusb_host2,
#endif
};
