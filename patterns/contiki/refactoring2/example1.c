#if !UIP_CONF_SIMPLE_JACKDAW_ADDR_TRANS
if(!mac_createEthernetAddr(
    (uint8_t *) &(ETHBUF(uip_buf)->src.addr[0]),
    (uip_lladdr_t *)packetbuf_addr(PACKETBUF_ADDR_SENDER)
  ))
#endif

  {
    mac_createDefaultEthernetAddr((uint8_t *) &(ETHBUF(uip_buf)->src.addr[0]));
  }
