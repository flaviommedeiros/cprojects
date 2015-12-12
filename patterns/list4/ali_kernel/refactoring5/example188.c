#ifdef CONFIG_PMAC_BACKLIGHT
if (M64_HAS(G3_PB_1_1) && machine_is_compatible("PowerBook1,1")) {
		/*
		 * these bits let the 101 powerbook
		 * wake up from sleep -- paulus
		 */
		aty_st_lcd(POWER_MANAGEMENT, aty_ld_lcd(POWER_MANAGEMENT, par) |
			   USE_F32KHZ | TRISTATE_MEM_EN, par);
	} else
#endif
	if (M64_HAS(MOBIL_BUS) && backlight) {
#ifdef CONFIG_FB_ATY_BACKLIGHT
		aty_bl_init(par);
#endif
	}
