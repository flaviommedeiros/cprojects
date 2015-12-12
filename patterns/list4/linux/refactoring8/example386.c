static unsigned short bfin_uart0_peripherals[] = {
	P_UART0_TX, P_UART0_RX,
#ifdef CONFIG_BFIN_UART0_CTSRTS
	P_UART0_RTS, P_UART0_CTS,
#endif
	0
};
