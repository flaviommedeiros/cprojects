#ifdef IPCONFIG_DHCP
if (ic_proto_enabled & IC_USE_DHCP)
		ic_dhcp_init_options(b->exten);
	else
#endif
		ic_bootp_init_ext(b->exten);
