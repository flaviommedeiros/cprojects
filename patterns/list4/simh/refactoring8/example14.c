MTAB rx_mod[] = {
    { UNIT_WLK, 0, "write enabled", "WRITEENABLED", NULL },
    { UNIT_WLK, UNIT_WLK, "write locked", "LOCKED", NULL },
#if defined (VM_PDP11)
    { MTAB_XTD|MTAB_VDV|MTAB_VALR, 004, "ADDRESS", "ADDRESS",
      &set_addr, &show_addr, NULL },
    { MTAB_XTD|MTAB_VDV, 0, NULL, "AUTOCONFIGURE",
      &set_addr_flt, NULL, NULL },
    { MTAB_XTD|MTAB_VDV|MTAB_VALR, 0, "VECTOR", "VECTOR",
      &set_vec, &show_vec, NULL },
#else
    { MTAB_XTD|MTAB_VDV, 004, "ADDRESS", "ADDRESS",
      NULL, &show_addr, NULL },
    { MTAB_XTD|MTAB_VDV, 0, "VECTOR", "VECTOR",
      NULL, &show_vec, NULL },
#endif
    { 0 }
    };
