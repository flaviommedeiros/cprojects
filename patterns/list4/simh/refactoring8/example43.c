DEVICE *sim_devices[] = {
    &cpu_dev,
    &clk_dev,
    &ptr_dev,
    &ptp_dev,
    &tti_dev,
    &tto_dev,
    &lpt_dev,
    &dt_dev,
    &drm_dev,
    &drp_dev,
    &dcs_dev,
    &dcsl_dev,
#if defined(USE_DISPLAY)
    &dpy_dev,
#endif
    NULL
    };
