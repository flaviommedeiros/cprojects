static struct map_desc cns3xxx_io_desc[] __initdata = {
	{
		.virtual	= CNS3XXX_TC11MP_SCU_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_TC11MP_SCU_BASE),
		.length		= SZ_8K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_TIMER1_2_3_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_TIMER1_2_3_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_MISC_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_MISC_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PM_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PM_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
#ifdef CONFIG_PCI
	}, {
		.virtual	= CNS3XXX_PCIE0_HOST_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_HOST_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE0_CFG0_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_CFG0_BASE),
		.length		= SZ_64K, /* really 4 KiB at offset 32 KiB */
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE0_CFG1_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_CFG1_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE1_HOST_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_HOST_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE1_CFG0_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_CFG0_BASE),
		.length		= SZ_64K, /* really 4 KiB at offset 32 KiB */
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE1_CFG1_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_CFG1_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
#endif
	},
};
