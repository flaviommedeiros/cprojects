MTAB tto_mod[] = {
#if !defined (KSR28)
    { TT_MODE, TT_MODE_KSR, "KSR", "KSR", &tty_set_mode },
    { TT_MODE, TT_MODE_7B,  "7b",  "7B",  &tty_set_mode },
    { TT_MODE, TT_MODE_8B,  "8b",  "8B",  &tty_set_mode },
    { TT_MODE, TT_MODE_7P,  "7p",  "7P",  &tty_set_mode },
#endif
    { MTAB_XTD|MTAB_VDV, 0, "DEVNO", NULL, NULL, &show_devno },
    { 0 }
    };
