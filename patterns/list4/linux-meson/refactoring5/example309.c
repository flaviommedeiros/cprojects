#ifdef CONFIG_BCMA_NFLASH
if (cc->nflash.boot) {
		base = BCMA_SOC_FLASH1;
		lim = BCMA_SOC_FLASH1_SZ;
	} else
#endif
	if (cc->pflash.present) {
		base = cc->pflash.window;
		lim = cc->pflash.window_size;
#ifdef CONFIG_BCMA_SFLASH
	} else if (cc->sflash.present) {
		base = cc->sflash.window;
		lim = cc->sflash.size;
#endif
	} else {
		pr_err("Couldn't find supported flash memory\n");
		return -ENXIO;
	}
