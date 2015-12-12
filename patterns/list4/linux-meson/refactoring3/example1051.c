switch (action) {
	case CPU_UP_PREPARE:
	case CPU_UP_PREPARE_FROZEN:
		pr_devel("MMU: Allocating stale context map for CPU %d\n", cpu);
		stale_map[cpu] = kzalloc(CTX_MAP_SIZE, GFP_KERNEL);
		break;
#ifdef CONFIG_HOTPLUG_CPU
	case CPU_UP_CANCELED:
	case CPU_UP_CANCELED_FROZEN:
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		pr_devel("MMU: Freeing stale context map for CPU %d\n", cpu);
		kfree(stale_map[cpu]);
		stale_map[cpu] = NULL;

		/* We also clear the cpu_vm_mask bits of CPUs going away */
		clear_tasks_mm_cpumask(cpu);
	break;
#endif /* CONFIG_HOTPLUG_CPU */
	}
