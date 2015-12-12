MTAB kmc_mod[] = {
    { MTAB_XTD|MTAB_VDV, 010, "ADDRESS", "ADDRESS",
        &set_addr, &show_addr, NULL, "Bus address" },
    { MTAB_XTD|MTAB_VDV|MTAB_VALR, 0, "VECTOR", "ADDRESS",
        &set_vec, &show_vec, NULL, "Interrupt vector" },
    { MTAB_XTD|MTAB_VDV|MTAB_VALR|MTAB_NMO, 0, "SPEED", "SPEED=dup=bps",
        &kmc_setLineSpeed, &kmc_showLineSpeed, NULL, "Line speed (bps)" },
    { MTAB_XTD|MTAB_VUN|MTAB_NMO, 1, "STATUS", NULL, NULL, &kmc_showStatus, NULL, "Display KMC status" },
#if KMC_UNITS > 1
    { MTAB_XTD|MTAB_VDV|MTAB_VALR, 0, "DEVICES", "DEVICES=n",
        &kmc_setDeviceCount, &kmc_showDeviceCount, NULL, "Display number of KMC devices enabled" },
#endif
    { 0 },
    };
