#ifndef RTN53
if(nvram_get_int("sw_mode") == SW_MODE_AP)
		strcpy(wan_ports, "lanports");
	else
#endif 
	if(wan_unit == 1)
		strcpy(wan_ports, "wan1ports");
	else
		strcpy(wan_ports, "wanports");
