static const unsigned int sic_iwr_irqs[] = {
#if defined(BF533_FAMILY)
	IRQ_PROG_INTB
#elif defined(BF537_FAMILY)
	IRQ_PROG_INTB, IRQ_PORTG_INTB, IRQ_MAC_TX
#elif defined(BF538_FAMILY)
	IRQ_PORTF_INTB
#elif defined(CONFIG_BF52x) || defined(CONFIG_BF51x)
	IRQ_PORTF_INTB, IRQ_PORTG_INTB, IRQ_PORTH_INTB
#elif defined(BF561_FAMILY)
	IRQ_PROG0_INTB, IRQ_PROG1_INTB, IRQ_PROG2_INTB
#else
# error no SIC_IWR defined
#endif
};
