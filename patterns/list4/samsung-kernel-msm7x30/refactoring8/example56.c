static struct pnp_fixup pnp_fixups[] = {
	/* Soundblaster awe io port quirk */
	{"CTL0021", quirk_awe32_resources},
	{"CTL0022", quirk_awe32_resources},
	{"CTL0023", quirk_awe32_resources},
	/* CMI 8330 interrupt and dma fix */
	{"@X@0001", quirk_cmi8330_resources},
	/* Soundblaster audio device io port range quirk */
	{"CTL0001", quirk_sb16audio_resources},
	{"CTL0031", quirk_sb16audio_resources},
	{"CTL0041", quirk_sb16audio_resources},
	{"CTL0042", quirk_sb16audio_resources},
	{"CTL0043", quirk_sb16audio_resources},
	{"CTL0044", quirk_sb16audio_resources},
	{"CTL0045", quirk_sb16audio_resources},
	/* Add IRQ-optional MPU options */
	{"ADS7151", quirk_ad1815_mpu_resources},
	{"ADS7181", quirk_add_irq_optional_dependent_sets},
	{"AZT0002", quirk_add_irq_optional_dependent_sets},
	/* PnP resources that might overlap PCI BARs */
	{"PNP0c01", quirk_system_pci_resources},
	{"PNP0c02", quirk_system_pci_resources},
#ifdef CONFIG_AMD_NB
	{"PNP0c01", quirk_amd_mmconfig_area},
#endif
	{""}
};
