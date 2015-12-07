if (http_port==SERVER_PORT ||
#ifdef RTCONFIG_HTTPS
	    http_port==SERVER_PORT_SSL ||
	    http_port==nvram_get_int("https_lanport") ||
#endif
		strcmp(nvram_get_x("PrinterStatus", "usb_webhttpcheck_x"), "1")==0) return 1;
	else return 0;
