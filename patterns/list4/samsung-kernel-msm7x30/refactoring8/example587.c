static struct mtd_partition bfin_spi_dataflash_partitions[] = {
	{
		.name   = "JFFS2 dataflash(nor)",
#ifdef CONFIG_MTD_PAGESIZE_1024
		.offset = 0x40000,
		.size   = 0x7C0000,
#else
		.offset = 0x0,
		.size   = 0x840000,
#endif
	}
};
