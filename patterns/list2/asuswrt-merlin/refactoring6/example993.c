if (
#ifdef BCMNVRAMW
		!nvram_inotp() &&
#endif
		commit) {
		printf("Committing NVRAM...");
		nvram_commit();
		printf("done\n");
		if (restore_defaults) {
#ifdef BCM_DEVINFO
                        /* devinfo nvram hash table sync */
                        devinfo_nvram_sync();
#endif
			printf("Waiting for wps button release...");
			reset_release_wait();
			printf("done\n");
		}
	}
