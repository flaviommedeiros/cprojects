#ifdef HAVE_IPV6
if (listen->family == AF_INET6) 
	{
	  for (addr = daemon->interface_addrs; addr; addr = addr->next)
	    if ((addr->flags & ADDRLIST_IPV6) &&
		is_same_net6(&addr->addr.addr.addr6, &source_addr.in6.sin6_addr, addr->prefixlen))
	      break;
	}
      else
#endif
	{
	  struct in_addr netmask;
	  for (addr = daemon->interface_addrs; addr; addr = addr->next)
	    {
	      netmask.s_addr = htonl(~(in_addr_t)0 << (32 - addr->prefixlen));
	      if (!(addr->flags & ADDRLIST_IPV6) &&
		  is_same_net(addr->addr.addr.addr4, source_addr.in.sin_addr, netmask))
		break;
	    }
	}
