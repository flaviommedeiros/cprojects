struct pm_domain_device domain_devices[] = {
		{ "A4LC", &lcdc_device, },
		{ "A4LC", &hdmi_lcdc_device, },
		{ "A4LC", &meram_device, },
		{ "A4MP", &fsi_device, },
		{ "A3SP", &usbhs0_device, },
		{ "A3SP", &usbhs1_device, },
		{ "A3SP", &nand_flash_device, },
		{ "A3SP", &sdhi0_device, },
#if !IS_ENABLED(CONFIG_MMC_SH_MMCIF)
		{ "A3SP", &sdhi1_device, },
#else
		{ "A3SP", &sh_mmcif_device, },
#endif
		{ "A3SP", &sdhi2_device, },
		{ "A4R", &ceu_device, },
	};
