#ifdef HAVE_IPV6
if (peer_addr->sa.sa_family == AF_INET6)
	{
	  nfct_set_attr_u8(ct, ATTR_L3PROTO, AF_INET6);
	  nfct_set_attr(ct, ATTR_IPV6_SRC, peer_addr->in6.sin6_addr.s6_addr);
	  nfct_set_attr_u16(ct, ATTR_PORT_SRC, peer_addr->in6.sin6_port);
	  nfct_set_attr(ct, ATTR_IPV6_DST, local_addr->addr.addr6.s6_addr);
	}
      else
#endif
	{
	  nfct_set_attr_u8(ct, ATTR_L3PROTO, AF_INET);
	  nfct_set_attr_u32(ct, ATTR_IPV4_SRC, peer_addr->in.sin_addr.s_addr);
	  nfct_set_attr_u16(ct, ATTR_PORT_SRC, peer_addr->in.sin_port);
	  nfct_set_attr_u32(ct, ATTR_IPV4_DST, local_addr->addr.addr4.s_addr);
	}
