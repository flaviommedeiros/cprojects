struct of_dev_auxdata versatile_auxdata_lookup[] __initdata = {
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_MMCI0_BASE, "fpga:05", &mmc0_plat_data),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_KMI0_BASE, "fpga:06", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_KMI1_BASE, "fpga:07", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_UART3_BASE, "fpga:09", NULL),
	/* FIXME: this is buggy, the platform data is needed for this MMC instance too */
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_MMCI1_BASE, "fpga:0b", NULL),

	OF_DEV_AUXDATA("arm,primecell", VERSATILE_CLCD_BASE, "dev:20", &clcd_plat_data),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_UART0_BASE, "dev:f1", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_UART1_BASE, "dev:f2", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_UART2_BASE, "dev:f3", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_SSP_BASE, "dev:f4", &ssp0_plat_data),

#if 0
	/*
	 * These entries are unnecessary because no clocks referencing
	 * them.  I've left them in for now as place holders in case
	 * any of them need to be added back, but they should be
	 * removed before actually committing this patch.  --gcl
	 */
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_AACI_BASE, "fpga:04", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_SCI1_BASE, "fpga:0a", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_SMC_BASE, "dev:00", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_MPMC_BASE, "dev:10", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_DMAC_BASE, "dev:30", NULL),

	OF_DEV_AUXDATA("arm,primecell", VERSATILE_SCTL_BASE, "dev:e0", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_WATCHDOG_BASE, "dev:e1", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_GPIO0_BASE, "dev:e4", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_GPIO1_BASE, "dev:e5", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_GPIO2_BASE, "dev:e6", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_GPIO3_BASE, "dev:e7", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_RTC_BASE, "dev:e8", NULL),
	OF_DEV_AUXDATA("arm,primecell", VERSATILE_SCI_BASE, "dev:f0", NULL),
#endif
	{}
};
