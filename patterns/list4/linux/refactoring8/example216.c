static const struct dmi_system_id __initconst cr48_dmi_table[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Cr-48 Chromebook (Codename Mario) */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "IEC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Mario"),
		},
	},
#endif
	{ }
};
