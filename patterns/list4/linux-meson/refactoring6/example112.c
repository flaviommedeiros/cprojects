if ((last_irq_sums[cpu] == sum)
#if defined(CONFIG_GDBSTUB) && defined(CONFIG_SMP)
			&& !(CHK_GDBSTUB_BUSY()
			     || atomic_read(&cpu_doing_single_step))
#endif
			) {
			/*
			 * Ayiee, looks like this CPU is stuck ...
			 * wait a few IRQs (5 seconds) before doing the oops ...
			 */
			watchdog_alert_counter[cpu]++;
			if (watchdog_alert_counter[cpu] == 5 * watchdog_hz) {
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
#ifdef CONFIG_SMP
				printk(KERN_ERR
				       "--- Register Dump (CPU%d) ---\n",
				       CPUID);
#endif
				show_registers(regs);
#ifdef CONFIG_SMP
				smp_nmi_call_function(watchdog_dump_register,
					NULL, 1);
#endif
				printk(KERN_NOTICE "console shuts up ...\n");
				console_silent();
				spin_unlock(&watchdog_print_lock);
				bust_spinlocks(0);
#ifdef CONFIG_GDBSTUB
				if (CHK_GDBSTUB_BUSY_AND_ACTIVE())
					gdbstub_exception(regs, excep);
				else
					gdbstub_intercept(regs, excep);
#endif
				do_exit(SIGSEGV);
			}
		} else {
			last_irq_sums[cpu] = sum;
			watchdog_alert_counter[cpu] = 0;
		}
