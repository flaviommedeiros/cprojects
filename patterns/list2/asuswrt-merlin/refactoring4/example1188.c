#if defined(RTCONFIG_RALINK_MT7620) || defined(RTCONFIG_RALINK_MT7621)
if(band == 0)
#else
		if(band == 1)
#endif
			aif = "apcli0";
		else
			aif = "apclii0";
