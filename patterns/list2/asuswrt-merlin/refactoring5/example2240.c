#ifdef CONFIG_MTD_PARTITIONS
if (info->nr_parts)
		del_mtd_partitions(info->mtd);
	else
#endif
		del_mtd_device(info->mtd);
