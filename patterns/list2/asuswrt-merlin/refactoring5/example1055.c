#ifdef CONFIG_PPC_ISERIES
if (firmware_has_feature(FW_FEATURE_ISERIES)) {
		if (strcmp(dev->type, "network") == 0)
			return &veth_iommu_table;
		return &vio_iommu_table;
	} else
#endif
	{
		const unsigned char *dma_window;
		struct iommu_table *tbl;
		unsigned long offset, size;

		dma_window = of_get_property(dev->dev.archdata.of_node,
					  "ibm,my-dma-window", NULL);
		if (!dma_window)
			return NULL;

		tbl = kmalloc(sizeof(*tbl), GFP_KERNEL);

		of_parse_dma_window(dev->dev.archdata.of_node, dma_window,
				    &tbl->it_index, &offset, &size);

		/* TCE table size - measured in tce entries */
		tbl->it_size = size >> IOMMU_PAGE_SHIFT;
		/* offset for VIO should always be 0 */
		tbl->it_offset = offset >> IOMMU_PAGE_SHIFT;
		tbl->it_busno = 0;
		tbl->it_type = TCE_VB;

		return iommu_init_table(tbl, -1);
	}
