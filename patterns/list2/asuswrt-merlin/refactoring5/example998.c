#ifdef MSC01E_INT_BASE
if (cpu_has_veic) {
		set_vi_handler (MSC01E_INT_PERFCTR, mips_perf_dispatch);
		cp0_perfcount_irq = MSC01E_INT_BASE + MSC01E_INT_PERFCTR;
	} else
#endif
	if (cp0_perfcount_irq >= 0) {
		if (cpu_has_vint)
			set_vi_handler(cp0_perfcount_irq, mips_perf_dispatch);
#ifdef CONFIG_MIPS_MT_SMTC
		setup_irq_smtc(cp0_perfcount_irq, irq,
		               0x100 << cp0_perfcount_irq);
#else
		setup_irq(cp0_perfcount_irq, irq);
#endif /* CONFIG_MIPS_MT_SMTC */
#ifdef CONFIG_SMP
		set_irq_handler(cp0_perfcount_irq, handle_percpu_irq);
#endif
	}
