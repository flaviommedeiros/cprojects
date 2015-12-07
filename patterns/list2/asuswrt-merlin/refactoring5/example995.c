#ifdef CONFIG_SIBYTE_BCM1480_PROF
if (pending & CAUSEF_IP7)	/* Cpu performance counter interrupt */
		sbprof_cpu_intr();
	else
#endif

	if (pending & CAUSEF_IP4)
		bcm1480_timer_interrupt();

#ifdef CONFIG_SMP
	else if (pending & CAUSEF_IP3)
		bcm1480_mailbox_interrupt();
#endif

#ifdef CONFIG_KGDB
	else if (pending & CAUSEF_IP6)
		bcm1480_kgdb_interrupt();		/* KGDB (uart 1) */
#endif

	else if (pending & CAUSEF_IP2) {
		unsigned long long mask_h, mask_l;
		unsigned long base;

		/*
		 * Default...we've hit an IP[2] interrupt, which means we've
		 * got to check the 1480 interrupt registers to figure out what
		 * to do.  Need to detect which CPU we're on, now that
		 * smp_affinity is supported.
		 */
		base = A_BCM1480_IMR_MAPPER(smp_processor_id());
		mask_h = __raw_readq(
			IOADDR(base + R_BCM1480_IMR_INTERRUPT_STATUS_BASE_H));
		mask_l = __raw_readq(
			IOADDR(base + R_BCM1480_IMR_INTERRUPT_STATUS_BASE_L));

		if (mask_h) {
			if (mask_h ^ 1)
				do_IRQ(fls64(mask_h) - 1);
			else
				do_IRQ(63 + fls64(mask_l));
		}
	}
