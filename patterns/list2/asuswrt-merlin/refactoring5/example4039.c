#ifdef RTCONFIG_WIRELESSREPEATER
if(nvram_get_int("sw_mode") == SW_MODE_REPEATER && nvram_get_int("wlc_state") != WLC_STATE_CONNECTED){
			dhcp_lease = atoi(nvram_default_get("dhcp_lease"));
		}
		else
#endif
		{
			dhcp_lease = nvram_get_int("dhcp_lease");
		}
