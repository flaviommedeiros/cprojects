REG lp647_reg[] = {
    { ORDATA (BUF, lp647_unit.buf, 8) },
    { FLDATA (INT, int_hwre[API_LPT], INT_V_LPT) },
    { FLDATA (DONE, lp647_don, 0) },
#if defined (PDP9)
    { FLDATA (ENABLE, lp647_ie, 0) },
#endif
    { FLDATA (ERR, lp647_err, 0) },
    { DRDATA (BPTR, lp647_bp, 7) },
    { ORDATA (SCMD, lp647_iot, 6), REG_HRO },
    { DRDATA (POS, lp647_unit.pos, T_ADDR_W), PV_LEFT },
    { DRDATA (TIME, lp647_unit.wait, 24), PV_LEFT },
    { FLDATA (STOP_IOE, lp647_stopioe, 0) },
    { BRDATA (LBUF, lp647_buf, 8, 8, LP647_BSIZE) },
    { ORDATA (DEVNO, lp647_dib.dev, 6), REG_HRO },
    { NULL }
    };
