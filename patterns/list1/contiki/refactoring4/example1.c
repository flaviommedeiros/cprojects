#if RESOLV_CONF_SUPPORTS_MDNS
if(++namemapptr->retries ==
             (namemapptr->is_mdns ? RESOLV_CONF_MAX_MDNS_RETRIES :
              RESOLV_CONF_MAX_RETRIES))
#else /* RESOLV_CONF_SUPPORTS_MDNS */
          if(++namemapptr->retries == RESOLV_CONF_MAX_RETRIES)
#endif /* RESOLV_CONF_SUPPORTS_MDNS */
          {
            /* Try the next server (if possible) before failing. Otherwise
               simply mark the entry as failed. */
            if(try_next_server(namemapptr) == 0) {
              /* STATE_ERROR basically means "not found". */
              namemapptr->state = STATE_ERROR;

#if RESOLV_SUPPORTS_RECORD_EXPIRATION
              /* Keep the "not found" error valid for 30 seconds */
              namemapptr->expiration = clock_seconds() + 30;
#endif /* RESOLV_SUPPORTS_RECORD_EXPIRATION */

              resolv_found(namemapptr->name, NULL);
              continue;
            }
          }
