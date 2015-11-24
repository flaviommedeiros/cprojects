if((namemapptr->state == STATE_UNUSED)
#if RESOLV_SUPPORTS_RECORD_EXPIRATION
          || (namemapptr->state == STATE_DONE && clock_seconds() > namemapptr->expiration)
#endif /* RESOLV_SUPPORTS_RECORD_EXPIRATION */
        ) {
          available_i = i;
        }
