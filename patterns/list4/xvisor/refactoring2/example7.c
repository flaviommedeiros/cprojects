#if SO_REUSE
if (!ip_get_option(pcb, SOF_REUSEADDR) ||
            !ip_get_option(cpcb, SOF_REUSEADDR))
#endif /* SO_REUSE */
        {
          if (ip_addr_isany(&(cpcb->local_ip)) ||
              ip_addr_isany(ipaddr) ||
              ip_addr_cmp(&(cpcb->local_ip), ipaddr)) {
            return ERR_USE;
          }
        }
