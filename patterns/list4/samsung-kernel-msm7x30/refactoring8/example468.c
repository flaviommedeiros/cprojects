static struct platform_device *mackerel_devices[] __initdata = {
	&nor_flash_device,
	&smc911x_device,
	&lcdc_device,
	&usbhs1_device,
	&usbhs0_device,
	&leds_device,
	&fsi_device,
	&fsi_ak4643_device,
	&fsi_hdmi_device,
	&nand_flash_device,
	&sdhi0_device,
#if !defined(CONFIG_MMC_SH_MMCIF) && !defined(CONFIG_MMC_SH_MMCIF_MODULE)
	&sdhi1_device,
#endif
	&sdhi2_device,
	&sh_mmcif_device,
	&ceu_device,
	&mackerel_camera,
	&hdmi_device,
	&hdmi_lcdc_device,
	&meram_device,
};
