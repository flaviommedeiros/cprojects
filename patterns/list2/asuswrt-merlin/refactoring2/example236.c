#ifdef RTCONFIG_DSL
if(get_dualwan_by_unit(wan_unit) == WANS_DUALWAN_IF_DSL)
#endif
	{
		if (nvram_match("dsltmp_adslsyncsts","up")) return 1;
		return 0;
	}
