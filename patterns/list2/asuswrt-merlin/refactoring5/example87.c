#ifdef RTCONFIG_OPENVPN
if (dnsstrict == 2)
		start_dnsmasq();	// add strict-order
	else
#endif
		reload_dnsmasq();
