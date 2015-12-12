static struct platform_device *mackerel_devices[] __initdata = {
	&nor_flash_device,
	&smc911x_device,
	&lcdc_device,
	&usbhs0_device,
	&usbhs1_device,
	&leds_device,
	&fsi_device,
	&fsi_ak4643_device,
	&fsi_hdmi_device,
	&nand_flash_device,
	&sdhi0_device,
#if !IS_ENABLED(CONFIG_MMC_SH_MMCIF)
	&sdhi1_device,
#else
	&sh_mmcif_device,
#endif
	&sdhi2_device,
	&ceu_device,
	&mackerel_camera,
	&hdmi_device,
	&hdmi_lcdc_device,
	&meram_device,
};
