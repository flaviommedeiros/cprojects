#ifdef RTCONFIG_BCMFA
if (FA_ON(fa_mode))
		return "vlan2";
	else
#endif
		return "eth0";
