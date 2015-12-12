#ifdef HAVE_IPV6
if (ipv6 && (family == 0 || family == AF_INET6)) {
		listener->family = AF_INET6;
		ret = init_socket (listener);
	} else
#endif
	{
		ret = ret_not_found;
	}
