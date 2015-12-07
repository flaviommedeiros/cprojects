if ((flags & F_IPV4) && (new->flags & F_IPV4) &&
	      new->addr.addr.addr.addr4.s_addr == addr->addr.addr4.s_addr)
	    return new;
#ifdef HAVE_IPV6
	  else if ((flags & F_IPV6) && (new->flags & F_IPV6) &&
		   IN6_ARE_ADDR_EQUAL(&new->addr.addr.addr.addr6, &addr->addr.addr6))
	    return new;
#endif
