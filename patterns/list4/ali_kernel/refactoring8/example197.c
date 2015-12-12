static struct dmi_system_id __initdata bad_bios_dmi_table[] = {
#ifdef CONFIG_X86_RESERVE_LOW_64K
	{
		.callback = dmi_low_memory_corruption,
		.ident = "AMI BIOS",
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOR, "American Megatrends Inc."),
		},
	},
	{
		.callback = dmi_low_memory_corruption,
		.ident = "Phoenix BIOS",
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix Technologies"),
		},
	},
	{
		.callback = dmi_low_memory_corruption,
		.ident = "Phoenix/MSC BIOS",
		.matches = {
			DMI_MATCH(DMI_BIOS_VENDOR, "Phoenix/MSC"),
		},
	},
	/*
	 * AMI BIOS with low memory corruption was found on Intel DG45ID and
	 * DG45FC boards.
	 * It has a different DMI_BIOS_VENDOR = "Intel Corp.", for now we will
	 * match only DMI_BOARD_NAME and see if there is more bad products
	 * with this vendor.
	 */
	{
		.callback = dmi_low_memory_corruption,
		.ident = "AMI BIOS",
		.matches = {
			DMI_MATCH(DMI_BOARD_NAME, "DG45ID"),
		},
	},
	{
		.callback = dmi_low_memory_corruption,
		.ident = "AMI BIOS",
		.matches = {
			DMI_MATCH(DMI_BOARD_NAME, "DG45FC"),
		},
	},
#endif
	{}
};
