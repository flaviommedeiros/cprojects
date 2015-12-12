asmlinkage
void watchdog_interrupt(struct pt_regs *regs, enum exception_code excep)
{

	/*
	 * Since current-> is always on the stack, and we always switch
	 * the stack NMI-atomically, it's safe to use smp_processor_id().
	 */
	int sum, cpu = smp_processor_id();
	int irq = NMIIRQ;
	u8 wdt, tmp;

	wdt = WDCTR & ~WDCTR_WDCNE;
	WDCTR = wdt;
	tmp = WDCTR;
	NMICR = NMICR_WDIF;

	nmi_count(cpu)++;
	kstat_incr_irqs_this_cpu(irq, irq_to_desc(irq));
	sum = irq_stat[cpu].__irq_count;

	if (last_irq_sums[cpu] == sum) {
		/*
		 * Ayiee, looks like this CPU is stuck ...
		 * wait a few IRQs (5 seconds) before doing the oops ...
		 */
		watchdog_alert_counter++;
		if (watchdog_alert_counter == 5 * watchdog_hz) {
			spin_lock(&watchdog_print_lock);
			/*
			 * We are in trouble anyway, lets at least try
			 * to get a message out.
			 */
			bust_spinlocks(1);
			printk(KERN_ERR
			       "NMI Watchdog detected LOCKUP on CPU%d,"
			       " pc %08lx, registers:\n",
			       cpu, regs->pc);
			show_registers(regs);
			printk("console shuts up ...\n");
			console_silent();
			spin_unlock(&watchdog_print_lock);
			bust_spinlocks(0);
#ifdef CONFIG_GDBSTUB
			if (gdbstub_busy)
				gdbstub_exception(regs, excep);
			else
				gdbstub_intercept(regs, excep);
#endif
			do_exit(SIGSEGV);
		}
	} else {
		last_irq_sums[cpu] = sum;
		watchdog_alert_counter = 0;
	}

	WDCTR = wdt | WDCTR_WDRST;
	tmp = WDCTR;
	WDCTR = wdt | WDCTR_WDCNE;
	tmp = WDCTR;
}
