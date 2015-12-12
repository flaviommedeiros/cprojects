#if LWIP_DHCP
if (check_ip_src)
#endif /* LWIP_DHCP */
  {  if ((ip_addr_isbroadcast(&(iphdr->src), inp)) ||
         (ip_addr_ismulticast(&(iphdr->src)))) {
      /* packet source is not valid */
      LWIP_DEBUGF(IP_DEBUG | LWIP_DBG_TRACE | 1, ("ip_input: packet source is not valid.\n"));
      /* free (drop) packet pbufs */
      pbuf_free(p);
      IP_STATS_INC(ip.drop);
      snmp_inc_ipinaddrerrors();
      snmp_inc_ipindiscards();
      return ERR_OK;
    }
  }
