if(fw->timer != 0 &&
#if UIP_REASSEMBLY > 0
       fw->len == BUF->len &&
       fw->offset == BUF->ipoffset &&
#endif
       fw->ipid == BUF->ipid &&
       uip_ipaddr_cmp(&fw->srcipaddr, &BUF->srcipaddr) &&
       uip_ipaddr_cmp(&fw->destipaddr, &BUF->destipaddr) &&
#if notdef
       fw->payload[0] == BUF->srcport &&
       fw->payload[1] == BUF->destport &&
#endif
       fw->proto == BUF->proto) {
      /* Drop packet. */
      return UIP_FW_FORWARDED;
    }
