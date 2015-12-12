#if IP_SOF_BROADCAST_RECV
if (ip_get_option(pcb, SOF_BROADCAST) || !ip_addr_isbroadcast(&current_iphdr_dest, inp))
#endif /* IP_SOF_BROADCAST_RECV */
      {
        /* receive callback function available? */
        if (pcb->recv != NULL) {
          /* the receive callback function did not eat the packet? */
          if (pcb->recv(pcb->recv_arg, pcb, p, ip_current_src_addr()) != 0) {
            /* receive function ate the packet */
            p = NULL;
            eaten = 1;
            if (prev != NULL) {
            /* move the pcb to the front of raw_pcbs so that is
               found faster next time */
              prev->next = pcb->next;
              pcb->next = raw_pcbs;
              raw_pcbs = pcb;
            }
          }
        }
        /* no receive callback function was set for this raw PCB */
      }
