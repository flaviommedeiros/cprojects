DEVICE *sim_devices[] = {
    &cpu_dev,
    &ptr_dev,
    &ptp_dev,
    &lpt_dev,
    &tty_dev,
    &mt_dev,
    &clk_dev,
    &fhd_dev,
    &dp_dev,
#ifdef VM_IMPTIP
    &wdt_dev,
    &rtc_dev,
    &imp_dev,
    &mi1_dev, &mi2_dev, &mi3_dev, &mi4_dev, &mi5_dev,
    &hi1_dev, &hi2_dev, &hi3_dev, &hi4_dev,
#endif
    NULL
    };
