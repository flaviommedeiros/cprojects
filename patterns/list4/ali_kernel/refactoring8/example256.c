static unsigned char irq_pri_vic1[] = {
#if defined (USE_PRIORITIES)
	IRQ_GPIO3INTR,			/* CPLD */
	IRQ_DMAM2P4, IRQ_DMAM2P5,	/* AC97 */
#endif
};
