if (family == AF_INET &&
		  tmp->addr.in.sin_addr.s_addr == addr->addr.addr4.s_addr)
		ret = match_addr = tmp->used = 1;
#ifdef HAVE_IPV6
	      else if (family == AF_INET6 &&
		       IN6_ARE_ADDR_EQUAL(&tmp->addr.in6.sin6_addr, 
					  &addr->addr.addr6))
		ret = match_addr = tmp->used = 1;
#endif
