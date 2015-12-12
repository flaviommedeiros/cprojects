MTAB sim_timer_mod[] = {
#if defined (SIM_ASYNCH_IO) && defined (SIM_ASYNCH_CLOCKS)
  { MTAB_VDV,          MTAB_VDV, "ASYNC", "ASYNC",   &sim_timer_set_async, &sim_timer_show_async, NULL, "Enables/Displays Asynchronous Timer operation mode" },
  { MTAB_VDV,                 0,    NULL, "NOASYNC", &sim_timer_clr_async, NULL,                  NULL, "Disables Asynchronous Timer operation" },
#endif
  { 0 },
};
