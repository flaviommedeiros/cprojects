#if LWIP_TCP_KEEPALIVE
if((u32_t)(tcp_ticks - pcb->tmr) > 
              (pcb->keep_idle + pcb->keep_cnt_sent * pcb->keep_intvl)
              / TCP_SLOW_INTERVAL)
#else
      else if((u32_t)(tcp_ticks - pcb->tmr) > 
              (pcb->keep_idle + pcb->keep_cnt_sent * TCP_KEEPINTVL_DEFAULT) 
              / TCP_SLOW_INTERVAL)
#endif /* LWIP_TCP_KEEPALIVE */
      {
        tcp_keepalive(pcb);
        pcb->keep_cnt_sent++;
      }
