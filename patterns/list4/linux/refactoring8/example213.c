static const struct dmi_system_id alps_dmi_has_separate_stick_buttons[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Extrapolated from other entries */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D420"),
		},
	},
	{
		/* Reported-by: Hans de Bruin <jmdebruin@xmsnet.nl> */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D430"),
		},
	},
	{
		/* Reported-by: Hans de Goede <hdegoede@redhat.com> */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D620"),
		},
	},
	{
		/* Extrapolated from other entries */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Latitude D630"),
		},
	},
#endif
	{ }
};
