struct testcase_t util_testcases[] = {
	{ "ipv4_parse", regress_ipv4_parse, 0, NULL, NULL },
	{ "ipv6_parse", regress_ipv6_parse, 0, NULL, NULL },
	{ "sockaddr_port_parse", regress_sockaddr_port_parse, 0, NULL, NULL },
	{ "sockaddr_port_format", regress_sockaddr_port_format, 0, NULL, NULL },
	{ "sockaddr_predicates", test_evutil_sockaddr_predicates, 0,NULL,NULL },
	{ "evutil_snprintf", test_evutil_snprintf, 0, NULL, NULL },
	{ "evutil_strtoll", test_evutil_strtoll, 0, NULL, NULL },
	{ "evutil_casecmp", test_evutil_casecmp, 0, NULL, NULL },
	{ "strlcpy", test_evutil_strlcpy, 0, NULL, NULL },
	{ "log", test_evutil_log, TT_FORK, NULL, NULL },
	{ "upcast", test_evutil_upcast, 0, NULL, NULL },
	{ "integers", test_evutil_integers, 0, NULL, NULL },
	{ "rand", test_evutil_rand, TT_FORK, NULL, NULL },
	{ "getaddrinfo", test_evutil_getaddrinfo, TT_FORK, NULL, NULL },
#ifdef WIN32
	{ "loadsyslib", test_evutil_loadsyslib, TT_FORK, NULL, NULL },
#endif
	END_OF_TESTCASES,
};
