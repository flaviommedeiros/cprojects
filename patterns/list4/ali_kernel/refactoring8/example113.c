static pcc_t pcc[] = {
#if !defined(CONFIG_PLAT_USRV)
	{ "m32r_cfc", 0 }, { "", 0 },
#else	/* CONFIG_PLAT_USRV */
	{ "m32r_cfc", 0 }, { "m32r_cfc", 0 }, { "m32r_cfc", 0 },
	{ "m32r_cfc", 0 }, { "m32r_cfc", 0 }, { "", 0 },
#endif	/* CONFIG_PLAT_USRV */
};
