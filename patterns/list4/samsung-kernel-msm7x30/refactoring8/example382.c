static struct platform_device *cdp_devices[] __initdata = {
	&msm_device_sps_apq8064,
#ifdef CONFIG_MSM_ROTATOR
       &msm_rotator_device,
#endif
};
