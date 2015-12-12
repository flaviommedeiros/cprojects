if ((!sim_idle_enab)                             ||     /* idling disabled */
    ((sim_clock_queue == QUEUE_LIST_END) &&             /* or clock queue empty? */
#if defined(SIM_ASYNCH_IO) && defined(SIM_ASYNCH_CLOCKS)
     (!(sim_asynch_enabled && sim_asynch_timer)))||     /*     and not asynch? */
#else
     (TRUE))                                     ||
#endif
    ((sim_clock_queue != QUEUE_LIST_END) && 
     ((sim_clock_queue->flags & UNIT_IDLE) == 0))||     /* or event not idle-able? */
    (rtc_elapsed[tmr] < sim_idle_stable)
