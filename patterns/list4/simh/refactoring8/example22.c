MTAB tu_mod[] = {
    { MTAB_XTD|MTAB_VDV, 0, "MASSBUS", NULL, 
        NULL, &mba_show_num, NULL, "Display Massbus number" },
#if defined (VM_PDP11)
    { MTAB_XTD|MTAB_VDV, 0, "FORMATTER", "TM02",
      &tu_set_fmtr, NULL         , NULL, "Set formatter/controller type to TM02" },
    { MTAB_XTD|MTAB_VDV, 1, NULL,        "TM03",
      &tu_set_fmtr, NULL,          NULL, "Set formatter/controller type to TM03" },
#endif
    { MTAB_XTD|MTAB_VDV, 0, "FORMATTER", NULL,
      NULL, &tu_show_fmtr, NULL, "Display formatter/controller type" },
    { MTUF_WLK,         0, "write enabled",  "WRITEENABLED", 
        NULL, NULL, NULL, "Write enable tape drive" },
    { MTUF_WLK,  MTUF_WLK, "write locked",   "LOCKED", 
        NULL, NULL, NULL, "Write lock tape drive"  },
    { UNIT_TYPE, UNIT_TE16, "TE16", "TE16", 
        NULL, NULL, NULL, "Set drive type to TE16" },
    { UNIT_TYPE, UNIT_TU45, "TU45", "TU45", 
        NULL, NULL, NULL, "Set drive type to TU45" },
    { UNIT_TYPE, UNIT_TU77, "TU77", "TU77", 
        NULL, NULL, NULL, "Set drive type to TU77" },
    { MTAB_XTD|MTAB_VUN|MTAB_VALR, 0,       "FORMAT", "FORMAT",
        &sim_tape_set_fmt, &sim_tape_show_fmt, NULL, "Set/Display tape format (SIMH, E11, TPC, P7B)" },
    { MTAB_XTD|MTAB_VUN|MTAB_VALR, 0,       "CAPACITY", "CAPACITY",
        &sim_tape_set_capac, &sim_tape_show_capac, NULL, "Set unit n capacity to arg MB (0 = unlimited)" },
    { MTAB_XTD|MTAB_VUN|MTAB_NMO, 0,        "CAPACITY", NULL,
        NULL,                &sim_tape_show_capac, NULL, "Set/Display capacity" },
    { 0 }
    };
