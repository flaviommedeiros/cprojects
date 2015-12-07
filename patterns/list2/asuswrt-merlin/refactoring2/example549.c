#ifdef RTCONFIG_USB_MODEM
if(strncmp(wan_ifname, "/dev/tty", 8))
#endif
	{
		if(strlen(wan_ifname) > 0){
			ifconfig(wan_ifname, 0, NULL, NULL);
#ifdef RTCONFIG_RALINK
#elif defined(RTCONFIG_QCA)
#else
			if(!strncmp(wan_ifname, "eth", 3) || !strncmp(wan_ifname, "vlan", 4))
				ifconfig(wan_ifname, IFUP, "0.0.0.0", NULL);
#endif
		}
	}
