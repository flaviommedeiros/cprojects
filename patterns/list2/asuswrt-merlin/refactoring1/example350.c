if (family == AF_INET)
	      {
		if (iface->addr.in.sin_addr.s_addr == addr->addr.addr4.s_addr)
		  return 1;
	      }
#ifdef HAVE_IPV6
	    else if (IN6_ARE_ADDR_EQUAL(&iface->addr.in6.sin6_addr, &addr->addr.addr6))
	      return 1;
#endif
