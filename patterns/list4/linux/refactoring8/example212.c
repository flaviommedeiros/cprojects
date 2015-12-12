static const struct dmi_system_id no_hw_res_dmi_table[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Gigabyte U2442 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "GIGABYTE"),
			DMI_MATCH(DMI_PRODUCT_NAME, "U2442"),
		},
	},
#endif
	{ }
};
