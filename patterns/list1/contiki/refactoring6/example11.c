if(uip_ds6_if.addr_list[i].isused
#if !RESOLV_CONF_MDNS_INCLUDE_GLOBAL_V6_ADDRS
       && uip_is_addr_linklocal(&uip_ds6_if.addr_list[i].ipaddr)
#endif
      ) {
      if(!*count) {
        queryptr = encode_name(queryptr, resolv_hostname);
      } else {
        /* Use name compression to refer back to the first name */
        *queryptr++ = 0xc0;
        *queryptr++ = sizeof(struct dns_hdr);
      }

      *queryptr++ = (uint8_t) ((NATIVE_DNS_TYPE) >> 8);
      *queryptr++ = (uint8_t) ((NATIVE_DNS_TYPE));

      *queryptr++ = (uint8_t) ((DNS_CLASS_IN | 0x8000) >> 8);
      *queryptr++ = (uint8_t) ((DNS_CLASS_IN | 0x8000));

      *queryptr++ = 0;
      *queryptr++ = 0;
      *queryptr++ = 0;
      *queryptr++ = 120;

      *queryptr++ = 0;
      *queryptr++ = sizeof(uip_ipaddr_t);

      uip_ipaddr_copy((uip_ipaddr_t*)queryptr, &uip_ds6_if.addr_list[i].ipaddr);
      queryptr += sizeof(uip_ipaddr_t);
      ++(*count);
    }
