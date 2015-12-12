const portSTACK_TYPE xInitialStack[] = {
        0x1111,	/* W1 */
        0x2222, /* W2 */
        0x3333, /* W3 */
        0x4444, /* W4 */
        0x5555, /* W5 */
        0x6666, /* W6 */
        0x7777, /* W7 */
        0x8888, /* W8 */
        0x9999, /* W9 */
        0xaaaa, /* W10 */
        0xbbbb, /* W11 */
        0xcccc, /* W12 */
        0xdddd, /* W13 */
        0xeeee, /* W14 */
        0xcdce, /* RCOUNT */
        0xabac, /* TBLPAG */

        /* dsPIC specific registers. */
#ifdef MPLAB_DSPIC_PORT
        0x0202, /* ACCAL */
        0x0303, /* ACCAH */
        0x0404, /* ACCAU */
        0x0505, /* ACCBL */
        0x0606, /* ACCBH */
        0x0707, /* ACCBU */
        0x0808, /* DCOUNT */
        0x090a, /* DOSTARTL */
        0x1010, /* DOSTARTH */
        0x1110, /* DOENDL */
        0x1212, /* DOENDH */
#endif
    };
