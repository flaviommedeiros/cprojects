#ifdef CONFIG_MTD_PARTITIONS
if (pdata->chip.part_probe_types) {
		res = parse_mtd_partitions(&data->mtd,
					pdata->chip.part_probe_types,
					&data->parts, 0);
		if (res > 0) {
			add_mtd_partitions(&data->mtd, data->parts, res);
			return 0;
		}
	}
