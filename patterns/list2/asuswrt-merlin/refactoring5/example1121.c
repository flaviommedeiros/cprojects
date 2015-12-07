#ifdef RTCONFIG_USB_MODEM
if (dualwan_unit__usbif(unit)) {
		if(!strcmp(wan_proto, "dhcp"))
			wan_ifname = nvram_safe_get(strcat_r(prefix, "ifname", tmp));
		else
			wan_ifname = nvram_safe_get(strcat_r(prefix, "pppoe_ifname", tmp));
	}
	else
#endif
	if(strcmp(wan_proto, "pppoe") == 0 ||
		strcmp(wan_proto, "pptp") == 0 ||
		strcmp(wan_proto, "l2tp") == 0)
		wan_ifname = nvram_safe_get(strcat_r(prefix, "pppoe_ifname", tmp));
	else
		wan_ifname = nvram_safe_get(strcat_r(prefix, "ifname", tmp));
