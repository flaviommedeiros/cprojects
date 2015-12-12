MTAB xu_mod[] = {
#if defined (VM_PDP11)
  { MTAB_XTD|MTAB_VDV|MTAB_VALR, 010, "ADDRESS", "ADDRESS",
    &set_addr, &show_addr, NULL },
  { MTAB_XTD|MTAB_VDV, 0, NULL, "AUTOCONFIGURE",
    &set_addr_flt, NULL, NULL },
  { MTAB_XTD|MTAB_VDV|MTAB_VALR, 0, "VECTOR", NULL,
    &set_vec, &show_vec, NULL },
#else
  { MTAB_XTD|MTAB_VDV, 0, "ADDRESS", NULL,
    NULL, &show_addr, NULL, "Unibus address" },
  { MTAB_XTD|MTAB_VDV, 0, "VECTOR", NULL,
    NULL, &show_vec, NULL, "Interrupt vector" },
#endif
  { MTAB_XTD|MTAB_VDV|MTAB_VALR, 0, "MAC", "MAC=xx:xx:xx:xx:xx:xx",
    &xu_setmac, &xu_showmac, NULL, "MAC address" },
  { MTAB_XTD |MTAB_VDV|MTAB_NMO, 0, "ETH", NULL,
    NULL, &eth_show, NULL, "Display attachable devices" },
  { MTAB_XTD|MTAB_VDV|MTAB_NMO, 0, "STATS", "STATS",
    &xu_set_stats, &xu_show_stats, NULL, "Display or reset statistics" },
  { MTAB_XTD|MTAB_VDV|MTAB_NMO, 0, "FILTERS", NULL,
    NULL, &xu_show_filters, NULL, "Display MAC addresses which will be received" },
  { MTAB_XTD|MTAB_VDV, 0, "TYPE", "TYPE={DEUNA|DELUA}",
    &xu_set_type, &xu_show_type, NULL, "Display the controller type" },
  { MTAB_XTD|MTAB_VDV|MTAB_VALR, 0, "THROTTLE", "THROTTLE=DISABLED|TIME=n{;BURST=n{;DELAY=n}}",
    &xu_set_throttle, &xu_show_throttle, NULL, "Display transmit throttle configuration" },
  { 0 },
};
