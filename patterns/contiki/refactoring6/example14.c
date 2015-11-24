if(strncasecmp(resolv_hostname, name, strlen(resolv_hostname)) == 0 &&
     ipaddr
#if NETSTACK_CONF_WITH_IPV6
     && !uip_ds6_is_my_addr(ipaddr)
#else
     && uip_ipaddr_cmp(&uip_hostaddr, ipaddr) != 0
#endif
    ) {
    uint8_t i;

    if(mdns_state == MDNS_STATE_PROBING) {
      /* We found this new name while probing.
       * We must now rename ourselves.
       */
      PRINTF("resolver: Name collision detected for \"%s\".\n", name);

      /* Remove the ".local" suffix. */
      resolv_hostname[strlen(resolv_hostname) - 6] = 0;

      /* Append the last three hex parts of the link-level address. */
      for(i = 0; i < 3; ++i) {
        uint8_t val = uip_lladdr.addr[(UIP_LLADDR_LEN - 3) + i];

        char append_str[4] = "-XX";

        append_str[2] = (((val & 0xF) > 9) ? 'a' : '0') + (val & 0xF);
        val >>= 4;
        append_str[1] = (((val & 0xF) > 9) ? 'a' : '0') + (val & 0xF);
        strncat(resolv_hostname, append_str,
                sizeof(resolv_hostname) - strlen(resolv_hostname) - 1); /* -1 in order to fit the terminating null byte. */
      }

      /* Re-add the .local suffix */
      strncat(resolv_hostname, ".local", RESOLV_CONF_MAX_DOMAIN_NAME_SIZE);

      start_name_collision_check(CLOCK_SECOND * 5);
    } else if(mdns_state == MDNS_STATE_READY) {
      /* We found a collision after we had already asserted
       * that we owned this name. We need to immediately
       * and explicitly begin probing.
       */
      PRINTF("resolver: Possible name collision, probing...\n");
      start_name_collision_check(0);
    }

  } else
#endif /* RESOLV_CONF_SUPPORTS_MDNS */

#if VERBOSE_DEBUG
  if(ipaddr) {
    PRINTF("resolver: Found address for \"%s\".\n", name);
    PRINTF
      ("resolver: %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x \n",
       ((uint8_t *) ipaddr)[0], ((uint8_t *) ipaddr)[1],
       ((uint8_t *) ipaddr)[2], ((uint8_t *) ipaddr)[3],
       ((uint8_t *) ipaddr)[4], ((uint8_t *) ipaddr)[5],
       ((uint8_t *) ipaddr)[6], ((uint8_t *) ipaddr)[7],
       ((uint8_t *) ipaddr)[8], ((uint8_t *) ipaddr)[9],
       ((uint8_t *) ipaddr)[10], ((uint8_t *) ipaddr)[11],
       ((uint8_t *) ipaddr)[12], ((uint8_t *) ipaddr)[13],
       ((uint8_t *) ipaddr)[14], ((uint8_t *) ipaddr)[15]);
  } else {
    PRINTF("resolver: Unable to retrieve address for \"%s\".\n", name);
  }
