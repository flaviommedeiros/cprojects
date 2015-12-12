switch (action) {
	case PM_SUSPEND_PREPARE:
	case PM_HIBERNATION_PREPARE:
		ret = bsp_check();
		break;
#ifdef CONFIG_DEBUG_HOTPLUG_CPU0
	case PM_RESTORE_PREPARE:
		/*
		 * When system resumes from hibernation, online CPU0 because
		 * 1. it's required for resume and
		 * 2. the CPU was online before hibernation
		 */
		if (!cpu_online(0))
			_debug_hotplug_cpu(0, 1);
		break;
	case PM_POST_RESTORE:
		/*
		 * When a resume really happens, this code won't be called.
		 *
		 * This code is called only when user space hibernation software
		 * prepares for snapshot device during boot time. So we just
		 * call _debug_hotplug_cpu() to restore to CPU0's state prior to
		 * preparing the snapshot device.
		 *
		 * This works for normal boot case in our CPU0 hotplug debug
		 * mode, i.e. CPU0 is offline and user mode hibernation
		 * software initializes during boot time.
		 *
		 * If CPU0 is online and user application accesses snapshot
		 * device after boot time, this will offline CPU0 and user may
		 * see different CPU0 state before and after accessing
		 * the snapshot device. But hopefully this is not a case when
		 * user debugging CPU0 hotplug. Even if users hit this case,
		 * they can easily online CPU0 back.
		 *
		 * To simplify this debug code, we only consider normal boot
		 * case. Otherwise we need to remember CPU0's state and restore
		 * to that state and resolve racy conditions etc.
		 */
		_debug_hotplug_cpu(0, 0);
		break;
#endif
	default:
		break;
	}
