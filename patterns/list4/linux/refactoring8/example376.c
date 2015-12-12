static unsigned short bfin_uart3_peripherals[] = {
	P_UART3_TX, P_UART3_RX,
#ifdef CONFIG_BFIN_UART3_CTSRTS
	P_UART3_RTS, P_UART3_CTS,
#endif
	0
};
