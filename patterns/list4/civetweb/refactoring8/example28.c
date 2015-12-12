static const char *valid[] = {
		"0",
		"1",
		"1s",
		"1r",
		"1.2.3.4:1",
		"1.2.3.4:1s",
		"1.2.3.4:1r",
#if defined(USE_IPV6)
		"[::1]:123",
		"[3ffe:2a00:100:7031::1]:900",
#endif
		NULL
	};
