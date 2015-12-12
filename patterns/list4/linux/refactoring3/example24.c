switch (hibernation_mode) {
	case HIBERNATION_REBOOT:
		kernel_restart(NULL);
		break;
	case HIBERNATION_PLATFORM:
		hibernation_platform_enter();
	case HIBERNATION_SHUTDOWN:
		if (pm_power_off)
			kernel_power_off();
		break;
#ifdef CONFIG_SUSPEND
	case HIBERNATION_SUSPEND:
		error = suspend_devices_and_enter(PM_SUSPEND_MEM);
		if (error) {
			if (hibernation_ops)
				hibernation_mode = HIBERNATION_PLATFORM;
			else
				hibernation_mode = HIBERNATION_SHUTDOWN;
			power_down();
		}
		/*
		 * Restore swap signature.
		 */
		error = swsusp_unmark();
		if (error)
			printk(KERN_ERR "PM: Swap will be unusable! "
			                "Try swapon -a.\n");
		return;
#endif
	}
