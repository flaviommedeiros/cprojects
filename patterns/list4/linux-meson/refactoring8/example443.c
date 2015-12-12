static struct resource s5p_uart4_resource[] = {
#if CONFIG_SERIAL_SAMSUNG_UARTS > 4
	[0] = DEFINE_RES_MEM(S5P_PA_UART4, S5P_SZ_UART),
	[1] = DEFINE_RES_IRQ(IRQ_UART4),
#endif
};
