TXsvfDoCmdFuncPtr   xsvf_pfDoCmd[]  =
{
    xsvfDoXCOMPLETE,        /*  0 */
    xsvfDoXTDOMASK,         /*  1 */
    xsvfDoXSIR,             /*  2 */
    xsvfDoXSDR,             /*  3 */
    xsvfDoXRUNTEST,         /*  4 */
    xsvfDoIllegalCmd,       /*  5 */
    xsvfDoIllegalCmd,       /*  6 */
    xsvfDoXREPEAT,          /*  7 */
    xsvfDoXSDRSIZE,         /*  8 */
    xsvfDoXSDRTDO,          /*  9 */
#ifdef  XSVF_SUPPORT_COMPRESSION
    xsvfDoXSETSDRMASKS,     /* 10 */
    xsvfDoXSDRINC,          /* 11 */
#else
    xsvfDoIllegalCmd,       /* 10 */
    xsvfDoIllegalCmd,       /* 11 */
#endif  /* XSVF_SUPPORT_COMPRESSION */
    xsvfDoXSDRBCE,          /* 12 */
    xsvfDoXSDRBCE,          /* 13 */
    xsvfDoXSDRBCE,          /* 14 */
    xsvfDoXSDRTDOBCE,       /* 15 */
    xsvfDoXSDRTDOBCE,       /* 16 */
    xsvfDoXSDRTDOBCE,       /* 17 */
    xsvfDoXSTATE,           /* 18 */
    xsvfDoXENDXR,           /* 19 */
    xsvfDoXENDXR,           /* 20 */
    xsvfDoXSIR2,            /* 21 */
    xsvfDoXCOMMENT,         /* 22 */
    xsvfDoXWAIT             /* 23 */
/* Insert new command functions here */
};
