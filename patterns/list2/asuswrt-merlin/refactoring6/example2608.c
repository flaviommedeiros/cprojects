if ((http_port != SERVER_PORT
#ifdef RTCONFIG_HTTPS
	  && http_port != SERVER_PORT_SSL
	  && http_port != nvram_get_int("https_lanport")
#endif
	    ) || login_ip_tmp == 0x100007f)
		//return 1;
		return 0;
