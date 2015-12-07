#ifdef RTCONFIG_YANDEXDNS
if (nvram_get_int("yadns_enable_x") && nvram_get_int("yadns_mode") != YADNS_DISABLED) {
		fprintf(fp, "no-resolv\n");	// no resolv
	} else
#endif
	fprintf(fp, "resolv-file=%s\n",		// the real stuff is here
		dmresolv);
