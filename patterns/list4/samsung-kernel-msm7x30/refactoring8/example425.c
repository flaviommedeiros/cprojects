static struct map_desc msm9625_io_desc[] __initdata = {
	MSM_CHIP_DEVICE(APCS_GCC, MSM9625),
	MSM_CHIP_DEVICE(TLMM, MSM9625),
	MSM_CHIP_DEVICE(TMR, MSM9625),
	{
		.virtual =  (unsigned long) MSM_SHARED_RAM_BASE,
		.length =   MSM_SHARED_RAM_SIZE,
		.type =     MT_DEVICE,
	},
#ifdef CONFIG_DEBUG_MSM9625_UART
	MSM_DEVICE(DEBUG_UART),
#endif
};
