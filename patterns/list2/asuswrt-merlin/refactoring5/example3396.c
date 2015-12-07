#ifdef CONFIG_MTD_PARTITIONS
if (pdata->chip.part_probe_types) {
		err = parse_mtd_partitions(&data->mtd,
					pdata->chip.part_probe_types,
					&data->parts, 0);
		if (err > 0) {
			add_mtd_partitions(&data->mtd, data->parts, err);
			return 0;
		}
	}
