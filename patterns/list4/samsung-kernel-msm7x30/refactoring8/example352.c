static struct clk_freq_tbl clk_tbl_mdp_lcdc[] = {
	F_MND16(       0, gnd,  1,   0,   0),
#if defined(CONFIG_MACH_ANCORA) || defined(CONFIG_MACH_ANCORA_TMO)
	F_MND16(24576000, pll3, 3,   1,  10),
	F_MND16(26482000, pll3, 1,   2,  29),
	F_MND16(30720000, pll3, 4,   1,   6),
	F_MND16(40960000, pll3, 2,   1,   9),
#else
	F_MND16(24576000, lpxo, 1,   0,   0),
	F_MND16(30720000, pll3, 4,   1,   6),
	F_MND16(32768000, pll3, 3,   2,  15),
	F_MND16(40960000, pll3, 2,   1,   9),
	F_MND16(73728000, pll3, 2,   1,   5),
#endif
	F_END,
};
