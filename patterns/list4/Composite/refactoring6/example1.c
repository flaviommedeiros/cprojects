if ((pcb->local_port == dest) &&
          (ip_addr_isany(&pcb->local_ip) ||
           ip_addr_cmp(&(pcb->local_ip), &(iphdr->dest)) || 
#if LWIP_IGMP
           ip_addr_ismulticast(&(iphdr->dest)) ||
#endif /* LWIP_IGMP */
           ip_addr_isbroadcast(&(iphdr->dest), inp))) {
        local_match = 1;
        if ((uncon_pcb == NULL) && 
            ((pcb->flags & UDP_FLAGS_CONNECTED) == 0)) {
          /* the first unconnected matching PCB */     
          uncon_pcb = pcb;
        }
      }
