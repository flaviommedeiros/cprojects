REG ptr_reg[] = {
    { ORDATA (BUF, ptr_unit.buf, 18) },
    { FLDATA (INT, int_hwre[API_PTR], INT_V_PTR) },
    { FLDATA (DONE, int_hwre[API_PTR], INT_V_PTR) },
#if defined (IOS_PTRERR)
    { FLDATA (ERR, ptr_err, 0) },
#endif
    { ORDATA (STATE, ptr_state, 5), REG_HRO },
    { DRDATA (POS, ptr_unit.pos, T_ADDR_W), PV_LEFT },
    { DRDATA (TIME, ptr_unit.wait, 24), PV_LEFT },
    { FLDATA (STOP_IOE, ptr_stopioe, 0) },
    { NULL }
    };
