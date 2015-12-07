#ifdef CONFIG_MIPS_MT_SMTC
if (!secondaryTC) {
#endif /* CONFIG_MIPS_MT_SMTC */

	if (cpu_has_veic || cpu_has_vint) {
		write_c0_ebase (ebase);
		/* Setting vector spacing enables EI/VI mode  */
		change_c0_intctl (0x3e0, VECTORSPACING);
	}
	if (cpu_has_divec) {
		if (cpu_has_mipsmt) {
			unsigned int vpflags = dvpe();
			set_c0_cause(CAUSEF_IV);
			evpe(vpflags);
		} else
			set_c0_cause(CAUSEF_IV);
	}

	/*
	 * Before R2 both interrupt numbers were fixed to 7, so on R2 only:
	 *
	 *  o read IntCtl.IPTI to determine the timer interrupt
	 *  o read IntCtl.IPPCI to determine the performance counter interrupt
	 */
	if (cpu_has_mips_r2) {
		cp0_compare_irq = (read_c0_intctl () >> 29) & 7;
		cp0_perfcount_irq = (read_c0_intctl () >> 26) & 7;
		if (cp0_perfcount_irq == cp0_compare_irq)
			cp0_perfcount_irq = -1;
	} else {
		cp0_compare_irq = CP0_LEGACY_COMPARE_IRQ;
		cp0_perfcount_irq = -1;
	}

#ifdef CONFIG_MIPS_MT_SMTC
	}
