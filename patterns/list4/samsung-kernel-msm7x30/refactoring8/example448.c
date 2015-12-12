static struct resource resources_sdc4[] = {
	{
		.name	= "core_mem",
		.start	= MSM_SDC4_BASE,
		.end	= MSM_SDC4_DML_BASE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.name	= "core_irq",
		.start	= SDC4_IRQ_0,
		.end	= SDC4_IRQ_0,
		.flags	= IORESOURCE_IRQ,
	},
#ifdef CONFIG_MMC_MSM_SPS_SUPPORT
	{
		.name   = "dml_mem",
		.start	= MSM_SDC4_DML_BASE,
		.end	= MSM_SDC4_BAM_BASE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.name   = "bam_mem",
		.start	= MSM_SDC4_BAM_BASE,
		.end	= MSM_SDC4_BAM_BASE + (2 * SZ_4K) - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.name   = "bam_irq",
		.start	= SDC4_BAM_IRQ,
		.end	= SDC4_BAM_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
#else
	{
		.name	= "dma_chnl",
		.start	= DMOV_SDC4_CHAN,
		.end	= DMOV_SDC4_CHAN,
		.flags	= IORESOURCE_DMA,
	},
	{
		.name	= "dma_crci",
		.start	= DMOV_SDC4_CRCI,
		.end	= DMOV_SDC4_CRCI,
		.flags	= IORESOURCE_DMA,
	},
#endif /* CONFIG_MMC_MSM_SPS_SUPPORT */
};
