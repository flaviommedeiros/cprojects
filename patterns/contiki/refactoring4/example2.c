#if RESOLV_SUPPORTS_RECORD_EXPIRATION
if(nanswers == 0 && UIP_UDP_BUF->srcport != UIP_HTONS(MDNS_PORT) 
      && hdr->id != 0)
#else
  if(nanswers == 0) 
#endif
  {
    if(try_next_server(namemapptr)) {
      namemapptr->state = STATE_ASKING;
      process_post(&resolv_process, PROCESS_EVENT_TIMER, NULL);
    }
  }
