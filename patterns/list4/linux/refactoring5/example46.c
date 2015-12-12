#ifdef CONFIG_OF
if (np)
		info = of_match_device(sh_pfc_of_table, &pdev->dev)->data;
	else
#endif
		info = platid ? (const void *)platid->driver_data : NULL;
