#if IP_ACCEPT_LINK_LAYER_ADDRESSING
if (check_ip_src && current_iphdr_src.addr != IPADDR_ANY)
#endif /* IP_ACCEPT_LINK_LAYER_ADDRESSING */
  {  if ((ip_addr_isbroadcast(&current_iphdr_src, inp)) ||
         (ip_addr_ismulticast(&current_iphdr_src))) {
      /* packet source is not valid */
      LWIP_DEBUGF(IP_DEBUG | LWIP_DBG_TRACE | LWIP_DBG_LEVEL_WARNING, ("ip_input: packet source is not valid.\n"));
      /* free (drop) packet pbufs */
      pbuf_free(p);
      IP_STATS_INC(ip.drop);
      snmp_inc_ipinaddrerrors();
      snmp_inc_ipindiscards();
      return ERR_OK;
    }
  }
