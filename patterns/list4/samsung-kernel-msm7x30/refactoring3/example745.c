switch (action) {
	case CPU_ONLINE:
	case CPU_ONLINE_FROZEN:
		register_cpu_online(cpu);
		break;
#ifdef CONFIG_HOTPLUG_CPU
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		unregister_cpu_online(cpu);
		break;
#endif
	}
