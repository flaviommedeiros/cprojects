static struct mtd_partition axis_default_partitions[NUM_DEFAULT_PARTITIONS] = {
	{
		.name = "boot firmware",
		.size = CONFIG_ETRAX_PTABLE_SECTOR,
		.offset = 0
	},
	{
		.name = "kernel",
		.size = 10 * CONFIG_ETRAX_PTABLE_SECTOR,
		.offset = CONFIG_ETRAX_PTABLE_SECTOR
	},
#define FILESYSTEM_SECTOR (11 * CONFIG_ETRAX_PTABLE_SECTOR)
#ifdef CONFIG_ETRAX_NANDBOOT
	{
		.name = "rootfs",
		.size = 10 * CONFIG_ETRAX_PTABLE_SECTOR,
		.offset = FILESYSTEM_SECTOR
	},
#undef FILESYSTEM_SECTOR
#define FILESYSTEM_SECTOR (21 * CONFIG_ETRAX_PTABLE_SECTOR)
#endif
	{
		.name = "rwfs",
		.size = DEFAULT_MEDIA_SIZE - FILESYSTEM_SECTOR,
		.offset = FILESYSTEM_SECTOR
	}
};
