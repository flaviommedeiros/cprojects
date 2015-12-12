static const struct iommu_platform_data omap3_iommu_pdata[] __initconst = {
	{
		.name = "isp",
		.nr_tlb_entries = 8,
		.clk_name = "cam_ick",
	},
#if defined(CONFIG_MPU_BRIDGE_IOMMU)
	{
		.name = "iva2",
		.nr_tlb_entries = 32,
		.clk_name = "iva2_ck",
	},
#endif
};
