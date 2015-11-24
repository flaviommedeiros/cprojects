#if !UIP_CONF_SIMPLE_JACKDAW_ADDR_TRANS
if(!mac_createEthernetAddr(UIP_ICMP_OPTS(icmp_opt_offset)->data, (uip_lladdr_t *)llbuf))
#endif
            mac_createDefaultEthernetAddr(UIP_ICMP_OPTS(icmp_opt_offset)->data);
