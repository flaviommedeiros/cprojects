#ifdef RTCONFIG_WIRELESSREPEATER
if(sw_mode == SW_MODE_REPEATER || sw_mode == SW_MODE_HOTSPOT)
		strcpy(dut_addr, DUT_DOMAIN_NAME);
	else
#endif
	if(isFirstUse)
		strcpy(dut_addr, DUT_DOMAIN_NAME);
	else
		strcpy(dut_addr, nvram_safe_get("lan_ipaddr"));
