static struct of_dev_auxdata plat_auxdata_lookup[] __initdata = {
#if defined(CONFIG_SERIAL_ARC) || defined(CONFIG_SERIAL_ARC_MODULE)
	OF_DEV_AUXDATA("snps,arc-uart", UART0_BASE, "arc-uart", arc_uart_info),
#endif
	{}
};
