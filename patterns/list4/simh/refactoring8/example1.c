unsigned short LP[] = {
    /* SECTION 1.  "rubber-band" dot-dash vector to tracking object. */

    SGM(GM_APOINT, IN_SAME, LP_SAME, BL_SAME, LT_SAME),
    APOINT(I_OFF, 01000, 01000),        /* screen center */

    SGM(GM_LVECT, IN_4, LP_DIS, BL_SAME, LT_DDASH),
    /* following coordinates are updated by LP hit intr. handler: */
    LVECT(I_ON, 0, 0),                  /* tracking object center */

    SGM(GM_SVECT, IN_7, LP_ENA, BL_SAME, LT_SOLID),
    SVECT(I_OFF, 0, 30),
    SVECT(I_ON, 0, -60),
    SVECT(I_OFF, 30, 30),
    SVECT(I_ON, -60, 0),
    SVECT(I_ON, 30, 30),
    SVECT(I_ON, 30, -30),
    SVECT(I_ON, -30, -30),
    SVECT(I_ON, -30, 30),
    SVECT(I_OFF, 10, 0),
    SVECT(I_ON, 20, 20),
    SVECT(I_ON, 20, -20),
    SVECT(I_ON, -20, -20),
    SVECT(I_ON, -20, 20),
    SVECT(I_OFF, 10, 0),
    SVECT(I_ON, 10, 10),
    SVECT(I_ON, 10, -10),
    SVECT(I_ON, -10, -10),
    SVECT(I_ON, -10, 10),
#if 0                                   /* not needed for this app */
    SVECT(I_OFF, 0, -10),               /* "flyback" vector */
#endif

    ENDSECT

    /* END OF TEST SECTIONS. */

    ENDFILE
};
