if ((http_port != SERVER_PORT
#ifdef RTCONFIG_HTTPS
	  && http_port != SERVER_PORT_SSL
	  && http_port != nvram_get_int("https_lanport")
#endif
	    ) || ip == 0x100007f)
		return;
