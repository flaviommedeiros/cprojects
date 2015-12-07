if ((nvram_get_int("qos_enable") == 1 && nvram_get_int("qos_type") == 0) || nvram_get_int("ctf_disable_force")
#ifndef RTCONFIG_BCMARM
	|| nvram_get_int("sw_mode") == SW_MODE_REPEATER
#endif
	|| nvram_get_int("cstats_enable") == 1
//#ifdef RTCONFIG_USB_MODEM
//	|| nvram_get_int("ctf_disable_modem")
//#endif
	) {
		nvram_set("ctf_disable", "1");
//		nvram_set("pktc_disable", "1");
	}
#ifdef RTCONFIG_BWDPI
	else if (check_bwdpi_nvram_setting() && nvram_get_int("sw_mode") == SW_MODE_ROUTER) {
		nvram_set("ctf_disable", "0");
	}
#endif
	else {
		nvram_set("ctf_disable", "0");
//		nvram_set("pktc_disable", "0");
	}
