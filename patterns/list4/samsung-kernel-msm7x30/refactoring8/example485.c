static struct platform_device *devices[] __initdata = {
#if defined(CONFIG_SOC_CAMERA_OV2640) || \
	defined(CONFIG_SOC_CAMERA_OV2640_MODULE)
	&isi_ov2640,
#endif
};
