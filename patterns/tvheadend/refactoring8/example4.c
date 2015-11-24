static linuxdvb_tbl_t guard_tbl[] = {
    { .t = DVB_GUARD_INTERVAL_AUTO,     .l = GUARD_INTERVAL_AUTO   },
    { .t = DVB_GUARD_INTERVAL_1_4,      .l = GUARD_INTERVAL_1_4    },
    { .t = DVB_GUARD_INTERVAL_1_8,      .l = GUARD_INTERVAL_1_8    },
    { .t = DVB_GUARD_INTERVAL_1_16,     .l = GUARD_INTERVAL_1_16   },
    { .t = DVB_GUARD_INTERVAL_1_32,     .l = GUARD_INTERVAL_1_32   },
#if DVB_VER_ATLEAST(5,3)
    { .t = DVB_GUARD_INTERVAL_1_128,    .l = GUARD_INTERVAL_1_128  },
    { .t = DVB_GUARD_INTERVAL_19_128,   .l = GUARD_INTERVAL_19_128 },
    { .t = DVB_GUARD_INTERVAL_19_256,   .l = GUARD_INTERVAL_19_256 },
#endif
    { .t = TABLE_EOD }
  };
