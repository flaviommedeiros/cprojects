REG clk_reg[] = {
    { FLDATA (INT, int_hwre[API_CLK], INT_V_CLK) },
    { FLDATA (DONE, int_hwre[API_CLK], INT_V_CLK) },
    { FLDATA (ENABLE, clk_state, 0) },
#if defined (PDP15)
    { ORDATA (TASKTIMER, clk_task_timer, 18) },
    { DRDATA (TASKLAST, clk_task_last, 32), REG_HRO },
#endif
    { DRDATA (TIME, clk_unit.wait, 24), REG_NZ + PV_LEFT },
    { DRDATA (TPS, clk_tps, 8), PV_LEFT + REG_HRO },
    { NULL }
    };
