static const struct dmi_system_id forcepad_dmi_table[] __initconst = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "HP EliteBook Folio 1040 G1"),
		},
	},
#endif
	{ }
};
