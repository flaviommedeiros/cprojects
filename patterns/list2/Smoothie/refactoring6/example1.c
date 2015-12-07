if(fw->timer != 0 &&
#if UIP_REASSEMBLY > 0
       fw->len == BUF->len &&
       fw->offset == BUF->ipoffset &&
#endif
       fw->ipid == BUF->ipid &&
       fw->srcipaddr[0] == BUF->srcipaddr[0] &&
       fw->srcipaddr[1] == BUF->srcipaddr[1] &&
       fw->destipaddr[0] == BUF->destipaddr[0] &&
       fw->destipaddr[1] == BUF->destipaddr[1] &&
#if notdef
       fw->payload[0] == BUF->srcport &&
       fw->payload[1] == BUF->destport &&
#endif
       fw->proto == BUF->proto) {
      /* Drop packet. */
      return UIP_FW_FORWARDED;
    }
