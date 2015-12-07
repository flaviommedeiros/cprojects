#ifdef CONFIG_NVRAM
if (default_cmode == CMODE_NVRAM){
		cmode = nvram_read_byte(NV_CMODE);
		if(cmode < CMODE_8 || cmode > CMODE_32)
			cmode = CMODE_8;
	} else
#endif
		cmode=default_cmode;
