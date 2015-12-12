if (ip_ver == 4) {
		*sock = socket(PF_INET, SOCK_STREAM, 0);
	}
#ifdef USE_IPV6
	else if (ip_ver == 6) {
		*sock = socket(PF_INET6, SOCK_STREAM, 0);
	}
#endif
