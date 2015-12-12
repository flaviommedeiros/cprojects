MTAB tti_mod[] = {
#if !defined (KSR28)
    { TT_MODE, TT_MODE_KSR, "KSR", "KSR", &tty_set_mode },
    { TT_MODE, TT_MODE_7B,  "7b",  "7B",  &tty_set_mode },
    { TT_MODE, TT_MODE_8B,  "8b",  "8B",  &tty_set_mode },
    { TT_MODE, TT_MODE_7P,  "7b",  NULL,  NULL },
#endif
    { TTUF_HDX, 0       , "full duplex", "FDX", NULL },
    { TTUF_HDX, TTUF_HDX, "half duplex", "HDX", NULL },
    { MTAB_XTD|MTAB_VDV, 0, "DEVNO", NULL, NULL, &show_devno, NULL },
    { 0 }
    };
