if(s->channel == packetbuf_attr(PACKETBUF_ATTR_CHANNEL)
#if NETSTACK_CONF_WITH_IPV6
       && s->proto == packetbuf_attr(PACKETBUF_ATTR_NETWORK_ID)
#endif
       ) {
      add_stats(s, input_or_output);
      break;
    }
