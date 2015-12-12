switch(action) {
	case CPU_UP_PREPARE:
	case CPU_UP_PREPARE_FROZEN:
		err = init_timers_cpu(cpu);
		if (err < 0)
			return notifier_from_errno(err);
		break;
#ifdef CONFIG_HOTPLUG_CPU
	case CPU_DEAD:
	case CPU_DEAD_FROZEN:
		migrate_timers(cpu);
		break;
#endif
	default:
		break;
	}
