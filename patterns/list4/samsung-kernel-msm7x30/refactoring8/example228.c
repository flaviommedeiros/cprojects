static const struct dmi_system_id min_max_dmi_table[] __initconst = {
#if defined(CONFIG_DMI)
	{
		/* Lenovo ThinkPad Helix */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad Helix"),
		},
		.driver_data = (int []){1024, 5052, 2258, 4832},
	},
	{
		/* Lenovo ThinkPad X240 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad X240"),
		},
		.driver_data = (int []){1232, 5710, 1156, 4696},
	},
	{
		/* Lenovo ThinkPad T440s */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T440"),
		},
		.driver_data = (int []){1024, 5112, 2024, 4832},
	},
	{
		/* Lenovo ThinkPad T540p */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "ThinkPad T540"),
		},
		.driver_data = (int []){1024, 5056, 2058, 4832},
	},
#endif
	{ }
};
