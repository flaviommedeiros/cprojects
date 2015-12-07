#if defined(CONFIG_NUMA)
if (cpumask_empty(non_isolated_cpus))
		cpumask_set_cpu(smp_processor_id(), non_isolated_cpus);
