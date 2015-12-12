return  ((TST_INT (PTP)? IOS_PTP: 0)
#if defined (IOS_PTPERR)
    | (ptp_err? IOS_PTPERR: 0)
#endif
    );
