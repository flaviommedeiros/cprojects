if (tmp->source_addr.sa.sa_family == AF_INET)
		tmp->source_addr.in.sin_port = htons(daemon->query_port);
#ifdef HAVE_IPV6
	      else if (tmp->source_addr.sa.sa_family == AF_INET6)
		tmp->source_addr.in6.sin6_port = htons(daemon->query_port);
#endif
