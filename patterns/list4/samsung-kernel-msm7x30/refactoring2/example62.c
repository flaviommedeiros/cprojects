#ifdef CONFIG_SERIAL_CONSOLE
if ((state - rs_table) != CONFIG_SERIAL_CONSOLE_PORT)
#endif
		sccp->scc_sccm &= ~(UART_SCCM_TX | UART_SCCM_RX);
