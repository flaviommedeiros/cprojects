#ifdef CONFIG_MTD_PARTITIONS
if (pdata->parts != NULL)
		r = add_mtd_partitions(&c->mtd, pdata->parts,
				       pdata->nr_parts);
	else
#endif
		r = add_mtd_device(&c->mtd);
