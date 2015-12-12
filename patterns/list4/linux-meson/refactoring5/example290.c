#ifdef CONFIG_OF
if (initial_boot_params)
		of_scan_flat_dt(exynos_fdt_map_chipid, NULL);
	else
#endif
		iotable_init(exynos_iodesc, ARRAY_SIZE(exynos_iodesc));
