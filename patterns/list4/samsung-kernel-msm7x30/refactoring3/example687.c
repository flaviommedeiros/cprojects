switch (action) {
	case CPU_UP_PREPARE:
	case CPU_UP_PREPARE_FROZEN:
		numa_setup_cpu(lcpu);
		ret = NOTIFY_OK;
		break;
#ifdef CONFIG_HOTPLUG_CPU
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
	case CPU_UP_CANCELED:
	case CPU_UP_CANCELED_FROZEN:
		unmap_cpu_from_node(lcpu);
		break;
		ret = NOTIFY_OK;
#endif
	}
