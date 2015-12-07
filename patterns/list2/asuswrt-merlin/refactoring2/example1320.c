#ifdef HAVE_IPV6
if (addr->sa.sa_family != AF_INET6 || !IN6_IS_ADDR_LINKLOCAL(&addr->in6.sin6_addr))
#endif
    {
      struct interface_name *int_name;
      struct addrlist *al;
#ifdef HAVE_AUTH
      struct auth_zone *zone;
      struct auth_name_list *name;

      /* Find subnets in auth_zones */
      for (zone = daemon->auth_zones; zone; zone = zone->next)
	for (name = zone->interface_names; name; name = name->next)
	  if (wildcard_match(name->name, label))
	    {
	      if (addr->sa.sa_family == AF_INET && (name->flags & AUTH4))
		{
		  if (param->spare)
		    {
		      al = param->spare;
		      param->spare = al->next;
		    }
		  else
		    al = whine_malloc(sizeof(struct addrlist));
		  
		  if (al)
		    {
		      al->next = zone->subnet;
		      zone->subnet = al;
		      al->prefixlen = prefixlen;
		      al->addr.addr.addr4 = addr->in.sin_addr;
		      al->flags = 0;
		    }
		}
	      
#ifdef HAVE_IPV6
	      if (addr->sa.sa_family == AF_INET6 && (name->flags & AUTH6))
		{
		  if (param->spare)
		    {
		      al = param->spare;
		      param->spare = al->next;
		    }
		  else
		    al = whine_malloc(sizeof(struct addrlist));
		  
		  if (al)
		    {
		      al->next = zone->subnet;
		      zone->subnet = al;
		      al->prefixlen = prefixlen;
		      al->addr.addr.addr6 = addr->in6.sin6_addr;
		      al->flags = ADDRLIST_IPV6;
		    }
		} 
#endif
	      
	    }
#endif
       
      /* Update addresses from interface_names. These are a set independent
	 of the set we're listening on. */  
      for (int_name = daemon->int_names; int_name; int_name = int_name->next)
	if (strncmp(label, int_name->intr, IF_NAMESIZE) == 0 && 
	    (addr->sa.sa_family == int_name->family || int_name->family == 0))
	  {
	    if (param->spare)
	      {
		al = param->spare;
		param->spare = al->next;
	      }
	    else
	      al = whine_malloc(sizeof(struct addrlist));
	    
	    if (al)
	      {
		al->next = int_name->addr;
		int_name->addr = al;
		
		if (addr->sa.sa_family == AF_INET)
		  {
		    al->addr.addr.addr4 = addr->in.sin_addr;
		    al->flags = 0;
		  }
#ifdef HAVE_IPV6
		else
		 {
		    al->addr.addr.addr6 = addr->in6.sin6_addr;
		    al->flags = ADDRLIST_IPV6;
		    /* Privacy addresses and addresses still undergoing DAD and deprecated addresses
		       don't appear in forward queries, but will in reverse ones. */
		    if (!(iface_flags & IFACE_PERMANENT) || (iface_flags & (IFACE_DEPRECATED | IFACE_TENTATIVE)))
		      al->flags |= ADDRLIST_REVONLY;
		 } 
#endif
	      }
	  }
    }
