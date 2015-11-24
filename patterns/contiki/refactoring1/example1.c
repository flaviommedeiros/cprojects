if(rxbuf[begin] == 'C') {
    int i;
    if(begin < end && (end - begin) >= 6
       && memcmp(&rxbuf[begin], "CLIENT", 6) == 0) {
      state = STATE_TWOPACKETS;	/* Interrupts do nothing. */
      memset(&rxbuf[begin], 0x0, 6);
      
      rxbuf_init();
      
      for(i = 0; i < 13; i++) {
	slip_arch_writeb("CLIENTSERVER\300"[i]);
      }
      return 0;
    }
  }
#ifdef SLIP_CONF_ANSWER_MAC_REQUEST
  else if(rxbuf[begin] == '?') { 
    /* Used by tapslip6 to request mac for auto configure */
    int i, j;
    char* hexchar = "0123456789abcdef";
    if(begin < end && (end - begin) >= 2
       && rxbuf[begin + 1] == 'M') {
      state = STATE_TWOPACKETS; /* Interrupts do nothing. */
      rxbuf[begin] = 0;
      rxbuf[begin + 1] = 0;
      
      rxbuf_init();
      
      linkaddr_t addr = get_mac_addr();
      /* this is just a test so far... just to see if it works */
      slip_arch_writeb('!');
      slip_arch_writeb('M');
      for(j = 0; j < 8; j++) {
        slip_arch_writeb(hexchar[addr.u8[j] >> 4]);
        slip_arch_writeb(hexchar[addr.u8[j] & 15]);
      }
      slip_arch_writeb(SLIP_END);
      return 0;
    }
  }
#endif
