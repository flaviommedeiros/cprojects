static struct iommu_device omap4_devices[] = {
	{
		.base = OMAP4_MMU1_BASE,
		.irq = OMAP44XX_IRQ_DUCATI_MMU,
		.pdata = {
			.name = "ducati",
			.nr_tlb_entries = 32,
			.clk_name = "ipu_fck",
			.da_start = 0x0,
			.da_end = 0xFFFFF000,
		},
	},
#if defined(CONFIG_MPU_TESLA_IOMMU)
	{
		.base = OMAP4_MMU2_BASE,
		.irq = INT_44XX_DSP_MMU,
		.pdata = {
			.name = "tesla",
			.nr_tlb_entries = 32,
			.clk_name = "tesla_ick",
			.da_start = 0x0,
			.da_end = 0xFFFFF000,
		},
	},
#endif
};
