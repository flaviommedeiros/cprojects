MTAB ry_mod[] = {
    { UNIT_WLK,                             0, "write enabled",     "WRITEENABLED", 
        NULL, NULL, NULL, "Write enable disk drive" },
    { UNIT_WLK,                      UNIT_WLK, "write locked",      "LOCKED", 
        NULL, NULL, NULL, "Write lock disk drive" },
    { (UNIT_DEN+UNIT_ATT),           UNIT_ATT, "single density",    NULL, NULL },
    { (UNIT_DEN+UNIT_ATT), (UNIT_DEN+UNIT_ATT), "double density",   NULL, NULL },
    { (UNIT_AUTO+UNIT_DEN+UNIT_ATT),         0, "single density",   NULL, NULL },
    { (UNIT_AUTO+UNIT_DEN+UNIT_ATT),  UNIT_DEN, "double density",   NULL, NULL },
    { (UNIT_AUTO+UNIT_ATT),          UNIT_AUTO, "autosize",         NULL, NULL },
    { UNIT_AUTO,                     UNIT_AUTO, NULL,               "AUTOSIZE", 
        NULL, NULL, NULL, "set density based on file size at ATTACH" },
    { (UNIT_AUTO+UNIT_DEN),                  0, NULL,               "SINGLE", 
        &ry_set_size, NULL, NULL, "Set to Single density (256Kb)" },
    { (UNIT_AUTO+UNIT_DEN),           UNIT_DEN, NULL,               "DOUBLE", 
        &ry_set_size, NULL, NULL, "Set to Double density (512Kb)" },
#if defined (VM_PDP11)
    { MTAB_XTD|MTAB_VDV|MTAB_VALR, 004, "ADDRESS", "ADDRESS",
      &set_addr, &show_addr, NULL, "Bus Address" },
    { MTAB_XTD | MTAB_VDV, 0, NULL, "AUTOCONFIGURE",
      &set_addr_flt, NULL, NULL, "Enable autoconfiguration of address & vector" },
    { MTAB_XTD|MTAB_VDV|MTAB_VALR, 0, "VECTOR", "VECTOR",
      &set_vec, &show_vec, NULL, "Interrupt vector" },
#else
    { MTAB_XTD|MTAB_VDV, 004, "ADDRESS", NULL,
      NULL, &show_addr, NULL, "Display Bus Address" },
    { MTAB_XTD|MTAB_VDV, 0, "VECTOR", NULL,
      NULL, &show_vec, NULL, "Display Interrupt vector" },
#endif
    { 0 }
    };
