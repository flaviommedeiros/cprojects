static char early_clks_name[EARLY_CLK_COUNT][32] = {
    //"HHI_VID_CLK_CNTL",
    //"HHI_VIID_CLK_CNTL",
#ifdef EARLY_SUSPEND_USE_XTAL
    "HHI_MPEG_CLK_CNTL",
#endif
};
