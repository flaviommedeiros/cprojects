if ((flags & RTF_UP) == (RTF_UP) && (inetaddr.s_addr & mask) == dest &&
#ifdef RTCONFIG_VPNC
		    (dest || strncmp(dev, "ppp", 3) || vpnc) /* avoid default via pppX to avoid on-demand loops*/)
#else
		    (dest || strncmp(dev, "ppp", 3))
