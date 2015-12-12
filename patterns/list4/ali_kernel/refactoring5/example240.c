#ifdef CONFIG_SIBYTE_BCM1480_PROF
if (pending & CAUSEF_IP7)	/* Cpu performance counter interrupt */
		sbprof_cpu_intr();
	else
#endif

	if (pending & CAUSEF_IP4)
		do_IRQ(K_BCM1480_INT_TIMER_0 + cpu);
#ifdef CONFIG_SMP
	else if (pending & CAUSEF_IP3)
		bcm1480_mailbox_interrupt();
#endif

	else if (pending & CAUSEF_IP2)
		dispatch_ip2();
