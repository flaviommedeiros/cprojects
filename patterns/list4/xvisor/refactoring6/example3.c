if (
           (!broadcast && ip_addr_isany(&pcb->local_ip)) ||
           ip_addr_cmp(&(pcb->local_ip), &current_iphdr_dest) ||
#if LWIP_IGMP
           ip_addr_ismulticast(&current_iphdr_dest) ||
#endif /* LWIP_IGMP */
#if IP_SOF_BROADCAST_RECV
            (broadcast && ip_get_option(pcb, SOF_BROADCAST) &&
             (ip_addr_isany(&pcb->local_ip) ||
              ip_addr_netcmp(&pcb->local_ip, ip_current_dest_addr(), &inp->netmask)))) {
#else /* IP_SOF_BROADCAST_RECV */
            (broadcast &&
             (ip_addr_isany(&pcb->local_ip) ||
              ip_addr_netcmp(&pcb->local_ip, ip_current_dest_addr(), &inp->netmask)))) {
#endif /* IP_SOF_BROADCAST_RECV */ 
          local_match = 1;
          if ((uncon_pcb == NULL) && 
              ((pcb->flags & UDP_FLAGS_CONNECTED) == 0)) {
            /* the first unconnected matching PCB */
            uncon_pcb = pcb;
          }
        }
