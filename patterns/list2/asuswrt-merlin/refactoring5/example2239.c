#ifdef CONFIG_MTD_PARTITIONS
if (dc21285_parts) {
		del_mtd_partitions(dc21285_mtd);
		kfree(dc21285_parts);
	} else
#endif
		del_mtd_device(dc21285_mtd);
