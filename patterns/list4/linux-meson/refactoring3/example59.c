switch (cmd) {
	case PMU_IOC_SLEEP:
		if (!capable(CAP_SYS_ADMIN))
			return -EACCES;
		return pm_suspend(PM_SUSPEND_MEM);
	case PMU_IOC_CAN_SLEEP:
		if (pmac_call_feature(PMAC_FTR_SLEEP_STATE, NULL, 0, -1) < 0)
			return put_user(0, argp);
		else
			return put_user(1, argp);

#ifdef CONFIG_PMAC_BACKLIGHT_LEGACY
	/* Compatibility ioctl's for backlight */
	case PMU_IOC_GET_BACKLIGHT:
	{
		int brightness;

		brightness = pmac_backlight_get_legacy_brightness();
		if (brightness < 0)
			return brightness;
		else
			return put_user(brightness, argp);

	}
	case PMU_IOC_SET_BACKLIGHT:
	{
		int brightness;

		error = get_user(brightness, argp);
		if (error)
			return error;

		return pmac_backlight_set_legacy_brightness(brightness);
	}
#ifdef CONFIG_INPUT_ADBHID
	case PMU_IOC_GRAB_BACKLIGHT: {
		struct pmu_private *pp = filp->private_data;

		if (pp->backlight_locker)
			return 0;

		pp->backlight_locker = 1;
		pmac_backlight_disable();

		return 0;
	}
#endif /* CONFIG_INPUT_ADBHID */
#endif /* CONFIG_PMAC_BACKLIGHT_LEGACY */

	case PMU_IOC_GET_MODEL:
	    	return put_user(pmu_kind, argp);
	case PMU_IOC_HAS_ADB:
		return put_user(pmu_has_adb, argp);
	}
