switch (action) {
	case CPU_UP_PREPARE:
	case CPU_UP_PREPARE_FROZEN:
		if (!zalloc_cpumask_var_node(&cfd->cpumask, GFP_KERNEL,
				cpu_to_node(cpu)))
			return notifier_from_errno(-ENOMEM);
		if (!zalloc_cpumask_var_node(&cfd->cpumask_ipi, GFP_KERNEL,
				cpu_to_node(cpu)))
			return notifier_from_errno(-ENOMEM);
		break;

#ifdef CONFIG_HOTPLUG_CPU
	case CPU_UP_CANCELED:
	case CPU_UP_CANCELED_FROZEN:

	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		free_cpumask_var(cfd->cpumask);
		free_cpumask_var(cfd->cpumask_ipi);
		break;
#endif
	}
