static struct resource resources_sdc5[] = {
	{
		.name	= "core_mem",
		.flags	= IORESOURCE_MEM,
		.start	= MSM_SDC5_BASE,
		.end	= MSM_SDC5_DML_BASE - 1,
	},
	{
		.name	= "core_irq",
		.flags	= IORESOURCE_IRQ,
		.start	= SDC5_IRQ_0,
		.end	= SDC5_IRQ_0
	},
#ifdef CONFIG_MMC_MSM_SPS_SUPPORT
	{
		.name   = "dml_mem",
		.start	= MSM_SDC5_DML_BASE,
		.end	= MSM_SDC5_BAM_BASE - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.name   = "bam_mem",
		.start	= MSM_SDC5_BAM_BASE,
		.end	= MSM_SDC5_BAM_BASE + (2 * SZ_4K) - 1,
		.flags	= IORESOURCE_MEM,
	},
	{
		.name   = "bam_irq",
		.start	= SDC5_BAM_IRQ,
		.end	= SDC5_BAM_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
#endif
};
