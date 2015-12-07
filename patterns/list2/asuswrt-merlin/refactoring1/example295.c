if (cache->flags & F_IPV4)
		  inet_ntop(AF_INET, &cache->addr.addr, a, ADDRSTRLEN);
#ifdef HAVE_IPV6
		else if (cache->flags & F_IPV6)
		  inet_ntop(AF_INET6, &cache->addr.addr, a, ADDRSTRLEN);
#endif
