if (state != ETHARP_STATE_EMPTY
#if ETHARP_SUPPORT_STATIC_ENTRIES
      && (state != ETHARP_STATE_STATIC)
#endif /* ETHARP_SUPPORT_STATIC_ENTRIES */
      ) {
      arp_table[i].ctime++;
      if ((arp_table[i].ctime >= ARP_MAXAGE) ||
          ((arp_table[i].state == ETHARP_STATE_PENDING)  &&
           (arp_table[i].ctime >= ARP_MAXPENDING))) {
        /* pending or stable entry has become old! */
        LWIP_DEBUGF(ETHARP_DEBUG, ("etharp_timer: expired %s entry %"U16_F".\n",
             arp_table[i].state >= ETHARP_STATE_STABLE ? "stable" : "pending", (u16_t)i));
        /* clean up entries that have just been expired */
        etharp_free_entry(i);
      }
      else if (arp_table[i].state == ETHARP_STATE_STABLE_REREQUESTING) {
        /* Reset state to stable, so that the next transmitted packet will
           re-send an ARP request. */
        arp_table[i].state = ETHARP_STATE_STABLE;
      }
#if ARP_QUEUEING
      /* still pending entry? (not expired) */
      if (arp_table[i].state == ETHARP_STATE_PENDING) {
        /* resend an ARP query here? */
      }
#endif /* ARP_QUEUEING */
    }
