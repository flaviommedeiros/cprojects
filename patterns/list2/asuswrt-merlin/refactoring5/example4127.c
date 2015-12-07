#ifdef RTCONFIG_WIRELESSREPEATER
if(nvram_get_int("sw_mode")==SW_MODE_REPEATER  && (mac=getStaMAC())!=NULL)	
		strncpy(router_mac, mac,sizeof(router_mac));	
	else   
#endif	   
		strcpy(router_mac, nvram_safe_get("et1macaddr"));
