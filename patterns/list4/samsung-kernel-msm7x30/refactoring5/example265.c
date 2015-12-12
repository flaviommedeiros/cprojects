#ifdef MSC01E_INT_BASE
if (cpu_has_veic) {
		/*
		 * Using platform specific interrupt controller defines.
		 */
		irq = MSC01E_INT_BASE + MSC01E_INT_PERFCTR;
	} else {
#endif
		if (cp0_perfcount_irq >= 0)
			irq = MIPS_CPU_IRQ_BASE + cp0_perfcount_irq;
		else
			irq = -1;
#ifdef MSC01E_INT_BASE
	}
