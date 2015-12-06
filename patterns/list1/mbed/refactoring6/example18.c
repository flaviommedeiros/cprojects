if ((pcb->local_port == dest) &&
          ((!broadcast && ip_addr_isany(&pcb->local_ip)) ||
           ip_addr_cmp(&(pcb->local_ip), &current_iphdr_dest) ||
#if LWIP_IGMP
           ip_addr_ismulticast(&current_iphdr_dest) ||
#endif /* LWIP_IGMP */
#if IP_SOF_BROADCAST_RECV
           (broadcast && (pcb->so_options & SOF_BROADCAST)))) {
#else  /* IP_SOF_BROADCAST_RECV */
           (broadcast))
