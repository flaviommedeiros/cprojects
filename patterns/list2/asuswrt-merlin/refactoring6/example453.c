if (
#ifdef BCMNVRAMW
		!nvram_inotp() &&
#endif
		commit) {
		printf("Committing NVRAM...");
		nvram_commit();
		printf("done\n");
		if (restore_defaults) {
			printf("Waiting for reset button release...");
			reset_release_wait();
			printf("done\n");
		}
	}
