static struct resource s5p_uart5_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 5
	[0] = DEFINE_RES_MEM(S5P_PA_UART5, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART5),
#endif
};
