#ifdef CONFIG_SIBYTE_SB1250_PROF
if (pending & CAUSEF_IP7) /* Cpu performance counter interrupt */
		sbprof_cpu_intr();
	else
#endif

	if (pending & CAUSEF_IP4)
		sb1250_timer_interrupt();

#ifdef CONFIG_SMP
	else if (pending & CAUSEF_IP3)
		sb1250_mailbox_interrupt();
#endif

#ifdef CONFIG_KGDB
	else if (pending & CAUSEF_IP6)			/* KGDB (uart 1) */
		sb1250_kgdb_interrupt();
#endif

	else if (pending & CAUSEF_IP2) {
		unsigned long long mask;

		/*
		 * Default...we've hit an IP[2] interrupt, which means we've
		 * got to check the 1250 interrupt registers to figure out what
		 * to do.  Need to detect which CPU we're on, now that
		 * smp_affinity is supported.
		 */
		mask = __raw_readq(IOADDR(A_IMR_REGISTER(smp_processor_id(),
		                              R_IMR_INTERRUPT_STATUS_BASE)));
		if (mask)
			do_IRQ(fls64(mask) - 1);
		else
			spurious_interrupt();
	} else
		spurious_interrupt();
