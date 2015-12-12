#ifdef CONFIG_SMP
if (pend0 & (1UL << CPU_RESCHED_A_IRQ)) {
		LOCAL_HUB_CLR_INTR(CPU_RESCHED_A_IRQ);
		scheduler_ipi();
	} else if (pend0 & (1UL << CPU_RESCHED_B_IRQ)) {
		LOCAL_HUB_CLR_INTR(CPU_RESCHED_B_IRQ);
		scheduler_ipi();
	} else if (pend0 & (1UL << CPU_CALL_A_IRQ)) {
		LOCAL_HUB_CLR_INTR(CPU_CALL_A_IRQ);
		smp_call_function_interrupt();
	} else if (pend0 & (1UL << CPU_CALL_B_IRQ)) {
		LOCAL_HUB_CLR_INTR(CPU_CALL_B_IRQ);
		smp_call_function_interrupt();
	} else
#endif
	{
		/* "map" swlevel to irq */
		struct slice_data *si = cpu_data[cpu].data;

		irq = si->level_to_irq[swlevel];
		do_IRQ(irq);
	}
