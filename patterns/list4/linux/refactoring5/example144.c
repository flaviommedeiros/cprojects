#ifdef CONFIG_MIPS_MT
if (cpu_online(cpu)) {
		cpumask_and(coupled_mask, cpu_online_mask,
			    &cpu_sibling_map[cpu]);
		online = cpumask_weight(coupled_mask);
		cpumask_clear_cpu(cpu, coupled_mask);
	} else
#endif
	{
		cpumask_clear(coupled_mask);
		online = 1;
	}
