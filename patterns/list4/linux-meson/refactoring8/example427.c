static unsigned early_clks[EARLY_CLK_COUNT] = {
	P_HHI_VID_CLK_CNTL,
	P_HHI_VIID_CLK_CNTL,
#ifdef EARLY_SUSPEND_USE_XTAL
	P_HHI_MPEG_CLK_CNTL,
#endif
};
