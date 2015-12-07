#if PASSTOS_CAPABILITY
if (flags & (PIPV4_PASSTOS|PIP_MSSFIX))
#else
      if (flags & PIP_MSSFIX)
#endif
	{
	  struct buffer ipbuf = *buf;
	  if (is_ipv4 (TUNNEL_TYPE (c->c1.tuntap), &ipbuf))
	    {
#if PASSTOS_CAPABILITY
	      /* extract TOS from IP header */
	      if (flags & PIPV4_PASSTOS)
		link_socket_extract_tos (c->c2.link_socket, &ipbuf);
#endif
			  
	      /* possibly alter the TCP MSS */
	      if (flags & PIP_MSSFIX)
		mss_fixup_ipv4 (&ipbuf, MTU_TO_MSS (TUN_MTU_SIZE_DYNAMIC (&c->c2.frame)));

#ifdef ENABLE_CLIENT_NAT
	      /* possibly do NAT on packet */
	      if ((flags & PIPV4_CLIENT_NAT) && c->options.client_nat)
		{
		  const int direction = (flags & PIPV4_OUTGOING) ? CN_INCOMING : CN_OUTGOING;
		  client_nat_transform (c->options.client_nat, &ipbuf, direction);
		}
#endif
	      /* possibly extract a DHCP router message */
	      if (flags & PIPV4_EXTRACT_DHCP_ROUTER)
		{
		  const in_addr_t dhcp_router = dhcp_extract_router_msg (&ipbuf);
		  if (dhcp_router)
		    route_list_add_vpn_gateway (c->c1.route_list, c->c2.es, dhcp_router);
		}
	    }
	  else if (is_ipv6 (TUNNEL_TYPE (c->c1.tuntap), &ipbuf))
	    {
	      /* possibly alter the TCP MSS */
	      if (flags & PIP_MSSFIX)
		mss_fixup_ipv6 (&ipbuf, MTU_TO_MSS (TUN_MTU_SIZE_DYNAMIC (&c->c2.frame)));
	    }
	}
