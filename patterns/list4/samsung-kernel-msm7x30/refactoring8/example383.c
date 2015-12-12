static struct dsi_cmd_desc lgit_power_on_set_1[] = {
	// Display Initial Set
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(lcd_mirror), lcd_mirror},

	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(panel_setting_1), panel_setting_1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(panel_setting_2), panel_setting_2},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(display_mode1), display_mode1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(display_mode2), display_mode2},

	// Gamma Set
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(p_gamma_r_setting), p_gamma_r_setting},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(n_gamma_r_setting), n_gamma_r_setting},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(p_gamma_g_setting), p_gamma_g_setting},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(n_gamma_g_setting), n_gamma_g_setting},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(p_gamma_b_setting), p_gamma_b_setting},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(n_gamma_b_setting), n_gamma_b_setting},

	// IEF set
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_on_set0), ief_on_set0},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_set1), ief_set1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_set2), ief_set2},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_set3), ief_set3},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_on_set4), ief_on_set4},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_on_set5), ief_on_set5},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_on_set6), ief_on_set6},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_set7), ief_set7},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_set8), ief_set8},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_set9), ief_set9},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_setA), ief_setA},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_setB), ief_setB},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(ief_setC), ief_setC},

	// Power Supply Set
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(osc_setting), osc_setting},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(power_setting3), power_setting3},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(power_setting4), power_setting4},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(power_setting5), power_setting5},

#ifdef CONFIG_LGIT_VIDEO_WXGA_CABC
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(cabc_set0), cabc_set0},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(cabc_set1), cabc_set1},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(cabc_set2), cabc_set2},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(cabc_set3), cabc_set3},
	{DTYPE_GEN_LWRITE, 1, 0, 0, 0, sizeof(cabc_set4), cabc_set4},
#endif
};
