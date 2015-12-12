static unsigned short bfin_uart1_peripherals[] = {
	P_UART1_TX, P_UART1_RX,
#ifdef CONFIG_BFIN_UART1_CTSRTS
	P_UART1_RTS, P_UART1_CTS,
#endif
	0
};
