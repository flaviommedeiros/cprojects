static struct iommu_device omap3_devices[] = {
	{
		.base = 0x480bd400,
		.irq = 24,
		.pdata = {
			.name = "isp",
			.nr_tlb_entries = 8,
			.clk_name = "cam_ick",
			.da_start = 0x0,
			.da_end = 0xFFFFF000,
		},
	},
#if defined(CONFIG_OMAP_IOMMU_IVA2)
	{
		.base = 0x5d000000,
		.irq = 28,
		.pdata = {
			.name = "iva2",
			.nr_tlb_entries = 32,
			.clk_name = "iva2_ck",
			.da_start = 0x11000000,
			.da_end = 0xFFFFF000,
		},
	},
#endif
};
