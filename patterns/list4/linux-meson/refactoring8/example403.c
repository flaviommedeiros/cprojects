static struct map_desc qsd8x50_io_desc[] __initdata = {
	MSM_DEVICE(VIC),
	MSM_CHIP_DEVICE(CSR, QSD8X50),
	MSM_DEVICE(DMOV),
	MSM_CHIP_DEVICE(GPIO1, QSD8X50),
	MSM_CHIP_DEVICE(GPIO2, QSD8X50),
	MSM_DEVICE(CLK_CTL),
	MSM_DEVICE(SIRC),
	MSM_DEVICE(SCPLL),
	MSM_DEVICE(AD5),
	MSM_DEVICE(MDC),
#if defined(CONFIG_DEBUG_MSM_UART1) || defined(CONFIG_DEBUG_MSM_UART2) || \
	defined(CONFIG_DEBUG_MSM_UART3)
	MSM_DEVICE(DEBUG_UART),
#endif
	{
		.virtual =  (unsigned long) MSM_SHARED_RAM_BASE,
		.pfn = __phys_to_pfn(MSM_SHARED_RAM_PHYS),
		.length =   MSM_SHARED_RAM_SIZE,
		.type =     MT_DEVICE,
	},
};
