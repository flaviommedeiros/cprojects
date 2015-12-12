REG tto_reg[] = {
    { ORDATA (BUF, tto_unit.buf, TTO_WIDTH) },
#if defined (KSR28)
    { FLDATA (SHIFT, tty_shift, 0), REG_HRO },
#endif
    { FLDATA (INT, int_hwre[API_TTO], INT_V_TTO) },
    { FLDATA (DONE, int_hwre[API_TTO], INT_V_TTO) },
    { DRDATA (POS, tto_unit.pos, T_ADDR_W), PV_LEFT },
    { DRDATA (TIME, tto_unit.wait, 24), PV_LEFT },
    { NULL }
    };
