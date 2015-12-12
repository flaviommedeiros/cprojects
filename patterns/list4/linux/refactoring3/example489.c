switch (action) {
	case CPU_UP_PREPARE:
	case CPU_UP_PREPARE_FROZEN:
		nid = numa_setup_cpu(lcpu);
		verify_cpu_node_mapping((int)lcpu, nid);
		ret = NOTIFY_OK;
		break;
#ifdef CONFIG_HOTPLUG_CPU
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
	case CPU_UP_CANCELED:
	case CPU_UP_CANCELED_FROZEN:
		unmap_cpu_from_node(lcpu);
		ret = NOTIFY_OK;
		break;
#endif
	}
