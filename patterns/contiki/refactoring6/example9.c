if(got_strobe_ack && (
#if NETSTACK_CONF_WITH_RIME
      packetbuf_attr(PACKETBUF_ATTR_RELIABLE) ||
      packetbuf_attr(PACKETBUF_ATTR_ERELIABLE) ||
#endif /* NETSTACK_CONF_WITH_RIME */
#if PACKETBUF_WITH_PACKET_TYPE
			packetbuf_attr(PACKETBUF_ATTR_PACKET_TYPE) ==
			PACKETBUF_ATTR_PACKET_TYPE_STREAM ||
#endif
      0)) {
    on(); /* Wait for ACK packet */
    waiting_for_packet = 1;
  } else {
    off();
  }
