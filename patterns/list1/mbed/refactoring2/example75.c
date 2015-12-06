#if SO_REUSE
if (((pcb->so_options & SOF_REUSEADDR) == 0) ||
          ((cpcb->so_options & SOF_REUSEADDR) == 0))
#endif /* SO_REUSE */
        {
          if (ip_addr_isany(&(cpcb->local_ip)) ||
              ip_addr_isany(ipaddr) ||
              ip_addr_cmp(&(cpcb->local_ip), ipaddr)) {
            return ERR_USE;
          }
        }
