static struct map_desc realview_pb11mp_io_desc[] __initdata = {
	{
		.virtual	= IO_ADDRESS(REALVIEW_SYS_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_SYS_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_PB11MP_GIC_CPU_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_PB11MP_GIC_CPU_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_PB11MP_GIC_DIST_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_PB11MP_GIC_DIST_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_TC11MP_GIC_CPU_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_TC11MP_GIC_CPU_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_TC11MP_GIC_DIST_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_TC11MP_GIC_DIST_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_SCTL_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_SCTL_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_PB11MP_TIMER0_1_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_PB11MP_TIMER0_1_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_PB11MP_TIMER2_3_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_PB11MP_TIMER2_3_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= IO_ADDRESS(REALVIEW_TC11MP_L220_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_TC11MP_L220_BASE),
		.length		= SZ_8K,
		.type		= MT_DEVICE,
	},
#ifdef CONFIG_DEBUG_LL
	{
		.virtual	= IO_ADDRESS(REALVIEW_PB11MP_UART0_BASE),
		.pfn		= __phys_to_pfn(REALVIEW_PB11MP_UART0_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
#endif
};
