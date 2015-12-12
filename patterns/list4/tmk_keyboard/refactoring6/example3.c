if ((mpcb->local_port == dest) &&
                ((!broadcast && ip_addr_isany(&mpcb->local_ip)) ||
                 ip_addr_cmp(&(mpcb->local_ip), &current_iphdr_dest) ||
#if LWIP_IGMP
                 ip_addr_ismulticast(&current_iphdr_dest) ||
#endif /* LWIP_IGMP */
#if IP_SOF_BROADCAST_RECV
                 (broadcast && (mpcb->so_options & SOF_BROADCAST)))) {
#else  /* IP_SOF_BROADCAST_RECV */
                 (broadcast))
