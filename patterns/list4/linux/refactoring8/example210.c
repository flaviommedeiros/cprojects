static const struct dmi_system_id elantech_dmi_has_middle_button[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Fujitsu H730 has a middle button */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CELSIUS H730"),
		},
	},
#endif
	{ }
};
