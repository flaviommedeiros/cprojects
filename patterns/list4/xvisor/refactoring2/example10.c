#if LWIP_AUTOIP
if (!ip_addr_islinklocal(&iphdr->src))
#endif /* LWIP_AUTOIP */
      {
        /* interface has default gateway? */
        if (!ip_addr_isany(&netif->gw)) {
          /* send to hardware address of default gateway IP address */
          dst_addr = &(netif->gw);
        /* no default gateway available */
        } else {
          /* no route to destination error (default gateway missing) */
          return ERR_RTE;
        }
      }
