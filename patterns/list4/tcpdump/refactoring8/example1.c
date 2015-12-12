static const struct tok nflog_values[] = {
	{ AF_INET,		"IPv4" },
#ifdef AF_INET6
	{ AF_INET6,		"IPv6" },
#endif /*AF_INET6*/
	{ 0,			NULL }
};
