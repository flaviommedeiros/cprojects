REG clk_reg[] = {
    { DRDATAD (TIME,                   clk_unit.wait,  24, "initial poll interval"), REG_NZ + PV_LEFT },
    { DRDATAD (POLL,                        tmr_poll,  24, "calibrated poll interval"), REG_NZ + PV_LEFT + REG_HRO },
    { DRDATAD (TPS,                          clk_tps,   8, "ticks per second (100)"), REG_NZ + PV_LEFT },
#if defined (SIM_ASYNCH_IO)
    { DRDATAD (ASYNCH,            sim_asynch_enabled,   1, "asynch I/O enabled flag"), PV_LEFT },
    { DRDATAD (LATENCY,           sim_asynch_latency,  32, "desired asynch interrupt latency"), PV_LEFT },
    { DRDATAD (INST_LATENCY, sim_asynch_inst_latency,  32, "calibrated instruction latency"), PV_LEFT },
#endif
    { NULL }
    };
