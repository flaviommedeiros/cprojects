if (
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "BR")) ||
#endif
			(!strcasecmp(countryCode, "BZ")) ||
			(!strcasecmp(countryCode, "BO")) ||
			(!strcasecmp(countryCode, "BN")) ||
			(!strcasecmp(countryCode, "CN")) ||
			(!strcasecmp(countryCode, "ID")) ||
			(!strcasecmp(countryCode, "IR")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "MO")) ||
#endif
			(!strcasecmp(countryCode, "PE")) ||
			(!strcasecmp(countryCode, "PH"))
#ifdef RTCONFIG_LOCALE2012
						 ||
			(!strcasecmp(countryCode, "VE"))
#endif
						 ||
#if defined(RTN65U)
			//for specific power
			(!strcasecmp(countryCode, "Z4")) 
#else
			0
#endif
	)
	{
		return 4;
	}
#ifndef RTCONFIG_LOCALE2012
	else if (	(!strcasecmp(countryCode, "KP")) ||
			(!strcasecmp(countryCode, "KR")) ||
			(!strcasecmp(countryCode, "UY")) ||
			(!strcasecmp(countryCode, "VE"))
	)
	{
		return 5;
	}
#else
	else if (!strcasecmp(countryCode, "RU"))
	{
		return 6;
	}
#endif
	else if (!strcasecmp(countryCode, "DB"))
	{
		return 7;
	}
	else if (
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "JP"))
#else
			(!strcasecmp(countryCode, "UA"))
#endif
	)
	{
		return 9;
	}
	else
	{
		if (warning)
			*warning = 2;
		return 7;
	}
