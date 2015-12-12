static const struct dmi_system_id elantech_dmi_force_crc_enabled[] = {
#if defined(CONFIG_DMI) && defined(CONFIG_X86)
	{
		/* Fujitsu H730 does not work with crc_enabled == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "CELSIUS H730"),
		},
	},
	{
		/* Fujitsu LIFEBOOK E554  does not work with crc_enabled == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E554"),
		},
	},
	{
		/* Fujitsu LIFEBOOK E544  does not work with crc_enabled == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK E544"),
		},
	},
	{
		/* Fujitsu LIFEBOOK U745 does not work with crc_enabled == 0 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "LIFEBOOK U745"),
		},
	},
#endif
	{ }
};
