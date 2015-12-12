static struct map_desc realview_eb_io_desc[] __initdata = {
	{
		.virtual	= IO_ADDRESS(REALVIEW_SYS_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_SYS_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_EB_GIC_CPU_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_EB_GIC_CPU_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_EB_GIC_DIST_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_EB_GIC_DIST_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_SCTL_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_SCTL_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_EB_TIMER0_1_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_EB_TIMER0_1_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_EB_TIMER2_3_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_EB_TIMER2_3_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
#ifdef CONFIG_DEBUG_LL
	{
		.virtual	= IO_ADDRESS(REALVIEW_EB_UART0_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_EB_UART0_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}
#endif
};
