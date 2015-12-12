#ifndef CONFIG_MACH_ARIESVE
if ((strcmp(dev->name, "accelerometer") == 0) || ((strcmp(dev->name, "compass_sensor") == 0) && (strcmp(handler->name, "cpufreq_ond")) == 0))
#else
		if ((strcmp(dev->name, "accelerometer") == 0) && (strcmp(handler->name, "cpufreq_ond") == 0))
#endif
			return -ENODEV;
