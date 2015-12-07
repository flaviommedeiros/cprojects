if (		(!strcasecmp(countryCode, "AE")) ||
			(!strcasecmp(countryCode, "AL")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "AR")) ||
#endif
			(!strcasecmp(countryCode, "AU")) ||
			(!strcasecmp(countryCode, "BH")) ||
			(!strcasecmp(countryCode, "BY")) ||
			(!strcasecmp(countryCode, "CA")) ||
			(!strcasecmp(countryCode, "CL")) ||
			(!strcasecmp(countryCode, "CO")) ||
			(!strcasecmp(countryCode, "CR")) ||
			(!strcasecmp(countryCode, "DO")) ||
			(!strcasecmp(countryCode, "DZ")) ||
			(!strcasecmp(countryCode, "EC")) ||
			(!strcasecmp(countryCode, "GT")) ||
			(!strcasecmp(countryCode, "HK")) ||
			(!strcasecmp(countryCode, "HN")) ||
			(!strcasecmp(countryCode, "IL")) ||
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "IN")) ||
#endif
			(!strcasecmp(countryCode, "JO")) ||
			(!strcasecmp(countryCode, "KW")) ||
			(!strcasecmp(countryCode, "KZ")) ||
			(!strcasecmp(countryCode, "LB")) ||
			(!strcasecmp(countryCode, "MA")) ||
			(!strcasecmp(countryCode, "MK")) ||
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "MO")) ||
			(!strcasecmp(countryCode, "MX")) ||
#endif
			(!strcasecmp(countryCode, "MY")) ||
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "NO")) ||
#endif
			(!strcasecmp(countryCode, "NZ")) ||
			(!strcasecmp(countryCode, "OM")) ||
			(!strcasecmp(countryCode, "PA")) ||
			(!strcasecmp(countryCode, "PK")) ||
			(!strcasecmp(countryCode, "PR")) ||
			(!strcasecmp(countryCode, "QA")) ||
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "RO")) ||
			(!strcasecmp(countryCode, "RU")) ||
#endif
			(!strcasecmp(countryCode, "SA")) ||
			(!strcasecmp(countryCode, "SG")) ||
			(!strcasecmp(countryCode, "SV")) ||
			(!strcasecmp(countryCode, "SY")) ||
			(!strcasecmp(countryCode, "TH")) ||
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "UA")) ||
#endif
			(!strcasecmp(countryCode, "US")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "UY")) ||
#endif
			(!strcasecmp(countryCode, "VN")) ||
			(!strcasecmp(countryCode, "YE")) ||
			(!strcasecmp(countryCode, "ZW")) ||
#if defined(RTN65U)
			//for specific power
			(!strcasecmp(countryCode, "Z1")) 
#else
			0
#endif
	)
	{
		return 0;
	}
	else if (
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "AM")) ||
#endif
			(!strcasecmp(countryCode, "AT")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "AZ")) ||
#endif
			(!strcasecmp(countryCode, "BE")) ||
			(!strcasecmp(countryCode, "BG")) ||
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "BR")) ||
#endif
			(!strcasecmp(countryCode, "CH")) ||
			(!strcasecmp(countryCode, "CY")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "CZ")) ||
#endif
			(!strcasecmp(countryCode, "DE")) ||
			(!strcasecmp(countryCode, "DK")) ||
			(!strcasecmp(countryCode, "EE")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "EG")) ||
#endif
			(!strcasecmp(countryCode, "ES")) ||
			(!strcasecmp(countryCode, "FI")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "FR")) ||
#endif
			(!strcasecmp(countryCode, "GB")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "GE")) ||
#endif
			(!strcasecmp(countryCode, "GR")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "HR")) ||
#endif
			(!strcasecmp(countryCode, "HU")) ||
			(!strcasecmp(countryCode, "IE")) ||
			(!strcasecmp(countryCode, "IS")) ||
			(!strcasecmp(countryCode, "IT")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "JP")) ||
			(!strcasecmp(countryCode, "KP")) ||
			(!strcasecmp(countryCode, "KR")) ||
#endif
			(!strcasecmp(countryCode, "LI")) ||
			(!strcasecmp(countryCode, "LT")) ||
			(!strcasecmp(countryCode, "LU")) ||
			(!strcasecmp(countryCode, "LV")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "MC")) ||
#endif
			(!strcasecmp(countryCode, "NL")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "NO")) ||
#endif
			(!strcasecmp(countryCode, "PL")) ||
			(!strcasecmp(countryCode, "PT")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "RO")) ||
#endif
			(!strcasecmp(countryCode, "SE")) ||
			(!strcasecmp(countryCode, "SI")) ||
			(!strcasecmp(countryCode, "SK")) ||
#ifdef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "TN")) ||
			(!strcasecmp(countryCode, "TR")) ||
			(!strcasecmp(countryCode, "TT")) ||
#endif
			(!strcasecmp(countryCode, "UZ")) ||
			(!strcasecmp(countryCode, "ZA")) ||
#if defined(RTN65U)
			//for specific power
			(!strcasecmp(countryCode, "Z2"))
#else
			0
#endif
	)
	{
		return 1;
	}
	else if (
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "AM")) ||
			(!strcasecmp(countryCode, "AZ")) ||
			(!strcasecmp(countryCode, "CZ")) ||
			(!strcasecmp(countryCode, "EG")) ||
			(!strcasecmp(countryCode, "FR")) ||
			(!strcasecmp(countryCode, "GE")) ||
			(!strcasecmp(countryCode, "HR")) ||
			(!strcasecmp(countryCode, "MC")) ||
			(!strcasecmp(countryCode, "TN")) ||
			(!strcasecmp(countryCode, "TR")) ||
			(!strcasecmp(countryCode, "TT"))
#else
			(!strcasecmp(countryCode, "IN")) ||
			(!strcasecmp(countryCode, "MX"))
#endif
	)
	{
		return 2;
	}
	else if (
#ifndef RTCONFIG_LOCALE2012
			(!strcasecmp(countryCode, "AR")) ||
#endif
			(!strcasecmp(countryCode, "TW")) ||
#if defined(RTN65U)
			//for specific power
			(!strcasecmp(countryCode, "Z3")) 
#else
			0
#endif
	)
	{
		return 3;
	}
	else if (
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
