static const struct pios_flash_partition pios_flash_partition_table[] = {
	{
		.label        = FLASH_PARTITION_LABEL_BL,
		.chip_desc    = &pios_flash_chip_internal,
		.first_sector = 0,
		.last_sector  = 1,
		.chip_offset  = 0,
		.size         = (1 - 0 + 1) * FLASH_SECTOR_16KB,
	},

	{
		.label        = FLASH_PARTITION_LABEL_SETTINGS,
		.chip_desc    = &pios_flash_chip_internal,
		.first_sector = 2,
		.last_sector  = 3,
		.chip_offset  = (2 * FLASH_SECTOR_16KB),
		.size         = (3 - 2 + 1) * FLASH_SECTOR_16KB,
	},

	/* NOTE: sector 4 of internal flash is currently unallocated */

	{
		.label        = FLASH_PARTITION_LABEL_FW,
		.chip_desc    = &pios_flash_chip_internal,
		.first_sector = 5,
		.last_sector  = 6,
		.chip_offset  = (4 * FLASH_SECTOR_16KB) + (1 * FLASH_SECTOR_64KB),
		.size         = (6 - 5 + 1) * FLASH_SECTOR_128KB,
	},

	/* NOTE: sectors 7-11 of the internal flash are currently unallocated */

#if defined (PIOS_INCLUDE_EXTERNAL_FLASH_WAYPOINTS)
	/* The waypoints are stored in an external flash chip */
	{
		.label        = FLASH_PARTITION_LABEL_WAYPOINTS,
		.chip_desc    = &pios_flash_chip_external,
		.first_sector = 16,
		.last_sector  = 31,
	},
#endif /* PIOS_INCLUDE_EXTERNAL_FLASH_WAYPOINTS */
};
