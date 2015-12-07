#ifdef MSC01E_INT_BASE
if (cpu_has_veic) {
		set_vi_handler(MSC01E_INT_PERFCTR, mips_perf_dispatch);
		mips_cpu_perf_irq = MSC01E_INT_BASE + MSC01E_INT_PERFCTR;
	} else
#endif
	if (cp0_perfcount_irq >= 0) {
		if (cpu_has_vint)
			set_vi_handler(cp0_perfcount_irq, mips_perf_dispatch);
		mips_cpu_perf_irq = MIPS_CPU_IRQ_BASE + cp0_perfcount_irq;
#ifdef CONFIG_SMP
		set_irq_handler(mips_cpu_perf_irq, handle_percpu_irq);
#endif
	}
