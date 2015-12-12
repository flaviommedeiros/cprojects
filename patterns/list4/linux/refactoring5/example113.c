#ifdef CONFIG_X86_LOCAL_APIC
if (m->inject_flags & (MCJ_IRQ_BROADCAST | MCJ_NMI_BROADCAST)) {
		unsigned long start;
		int cpu;

		get_online_cpus();
		cpumask_copy(mce_inject_cpumask, cpu_online_mask);
		cpumask_clear_cpu(get_cpu(), mce_inject_cpumask);
		for_each_online_cpu(cpu) {
			struct mce *mcpu = &per_cpu(injectm, cpu);
			if (!mcpu->finished ||
			    MCJ_CTX(mcpu->inject_flags) != MCJ_CTX_RANDOM)
				cpumask_clear_cpu(cpu, mce_inject_cpumask);
		}
		if (!cpumask_empty(mce_inject_cpumask)) {
			if (m->inject_flags & MCJ_IRQ_BROADCAST) {
				/*
				 * don't wait because mce_irq_ipi is necessary
				 * to be sync with following raise_local
				 */
				preempt_disable();
				smp_call_function_many(mce_inject_cpumask,
					mce_irq_ipi, NULL, 0);
				preempt_enable();
			} else if (m->inject_flags & MCJ_NMI_BROADCAST)
				apic->send_IPI_mask(mce_inject_cpumask,
						NMI_VECTOR);
		}
		start = jiffies;
		while (!cpumask_empty(mce_inject_cpumask)) {
			if (!time_before(jiffies, start + 2*HZ)) {
				printk(KERN_ERR
				"Timeout waiting for mce inject %lx\n",
					*cpumask_bits(mce_inject_cpumask));
				break;
			}
			cpu_relax();
		}
		raise_local();
		put_cpu();
		put_online_cpus();
	} else
#endif
	{
		preempt_disable();
		raise_local();
		preempt_enable();
	}
