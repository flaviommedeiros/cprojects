#ifdef HAVE_IPV6
if (flags & F_IPV6) 
    {
      addr->pfra_af = AF_INET6;
      addr->pfra_net = 0x80;
      memcpy(&(addr->pfra_ip6addr), &(ipaddr->addr), sizeof(struct in6_addr));
    } 
  else 
#endif
    {
      addr->pfra_af = AF_INET;
      addr->pfra_net = 0x20;
      addr->pfra_ip4addr.s_addr = ipaddr->addr.addr4.s_addr;
    }
