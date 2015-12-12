static struct platform_device *devices[] __initdata = {
#if !defined(CONFIG_MSM_SERIAL_DEBUGGER)
	&msm_device_uart3,
#endif
	&msm_device_smd,
	&msm_device_dmov,
	&msm_device_nand,
	&msm_device_hsusb,
	&usb_mass_storage_device,
	&android_usb_device,
	&fish_battery_device,
	&smc91x_device,
	&msm_device_touchscreen,
	&android_pmem_mdp_device,
	&android_pmem_adsp_device,
	&android_pmem_gpu0_device,
	&android_pmem_gpu1_device,
	&msm_kgsl_device,
};
