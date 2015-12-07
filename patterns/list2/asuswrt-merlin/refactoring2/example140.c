#if ENABLE_FEATURE_IPV6
if (family == AF_INET)
#endif
			setsockopt(fd, IPPROTO_IP, IP_TOS, &const_IPTOS_LOWDELAY, sizeof(const_IPTOS_LOWDELAY));
