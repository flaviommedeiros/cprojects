REG ptp_reg[] = {
    { ORDATA (BUF, ptp_unit.buf, 8) },
    { FLDATA (INT, int_hwre[API_PTP], INT_V_PTP) },
    { FLDATA (DONE, int_hwre[API_PTP], INT_V_PTP) },
#if defined (IOS_PTPERR)
    { FLDATA (ERR, ptp_err, 0) },
#endif
    { DRDATA (POS, ptp_unit.pos, T_ADDR_W), PV_LEFT },
    { DRDATA (TIME, ptp_unit.wait, 24), PV_LEFT },
    { FLDATA (STOP_IOE, ptp_stopioe, 0) },
    { NULL }
    };
