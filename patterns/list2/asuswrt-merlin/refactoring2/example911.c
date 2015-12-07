#if ENABLE_FEATURE_OSF_LABEL
if (bsd_trydev(device) < 0)
#endif
			printf("Disk %s doesn't contain a valid "
				"partition table\n", device);
