static struct resource s5p_uart3_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 3
	[0] = DEFINE_RES_MEM(S5P_PA_UART3, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART3),
#endif
};
