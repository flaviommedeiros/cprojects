DEVICE *sim_devices[] = {
    &cpu_dev,
#if defined (ECLIPSE)
    &map_dev,
    &fpu_dev,
    &pit_dev,
#endif
    &ptr_dev,
    &ptp_dev,
    &tti_dev,
    &tto_dev,
    &tti1_dev,
    &tto1_dev,
    &clk_dev,
    &plt_dev,
    &lpt_dev,
    &dsk_dev,
    &dkp_dev,
    &mta_dev,
    &qty_dev,
    &alm_dev,
    NULL
    };
