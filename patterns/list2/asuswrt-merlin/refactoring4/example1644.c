#if defined(BCMHOSTVARS)
if (base && (base != mfgsromvars))
#else
	if (base)
#endif 
		MFREE(osh, base, MAXSZ_NVRAM_VARS);
