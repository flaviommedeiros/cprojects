#ifdef DUAL_IMAGE
if (!nvram_get(IMAGE_BOOT))
#else
	if (!nvram_get(BOOTPARTITION))
#endif
		return 0;
