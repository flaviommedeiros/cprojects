static struct resource resources_sdc3[] = {
	{
		.name	= "core_mem",
		.start	= MSM_SDC3_BASE,
		.end	= MSM_SDC3_DML_BASE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.name	= "core_irq",
		.start	= SDC3_IRQ_0,
		.end	= SDC3_IRQ_0,
		.flags	= IORESOURCE_IRQ,
	},
#ifdef CONFIG_MMC_MSM_SPS_SUPPORT
	{
		.name   = "dml_mem",
		.start	= MSM_SDC3_DML_BASE,
		.end	= MSM_SDC3_BAM_BASE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.name   = "bam_mem",
		.start	= MSM_SDC3_BAM_BASE,
		.end	= MSM_SDC3_BAM_BASE + (2 * SZ_4K) - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.name   = "bam_irq",
		.start	= SDC3_BAM_IRQ,
		.end	= SDC3_BAM_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
#else
	{
		.name	= "dma_chnl",
		.start	= DMOV_SDC3_CHAN,
		.end	= DMOV_SDC3_CHAN,
		.flags	= IORESOURCE_DMA,
	},
	{
		.name	= "dma_crci",
		.start	= DMOV_SDC3_CRCI,
		.end	= DMOV_SDC3_CRCI,
		.flags	= IORESOURCE_DMA,
	},
#endif /* CONFIG_MMC_MSM_SPS_SUPPORT */
};
