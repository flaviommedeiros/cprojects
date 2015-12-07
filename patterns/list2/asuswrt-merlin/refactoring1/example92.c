if (tmp->addr.sa.sa_family == AF_INET)
	  tmp->addr.in.sin_port = htons(daemon->port);
#ifdef HAVE_IPV6
	else if (tmp->addr.sa.sa_family == AF_INET6)
	  tmp->addr.in6.sin6_port = htons(daemon->port);
#endif
