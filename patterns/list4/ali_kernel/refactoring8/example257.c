static unsigned char irq_pri_vic2[] = {
#if defined (USE_PRIORITIES)
	IRQ_T3UI,			/* Timer */
	IRQ_GPIO7INTR,			/* CPLD */
	IRQ_UART1INTR, IRQ_UART2INTR, IRQ_UART3INTR,
	IRQ_LCDINTR,			/* LCD */
	IRQ_TSCINTR,			/* ADC/Touchscreen */
#endif
};
