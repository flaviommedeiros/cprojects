#ifdef CONFIG_FB_PXA_SMARTPANEL
if (fbi->lccr0 & LCCR0_LCDT)
		setup_smart_timing(fbi, var);
	else
#endif
		setup_parallel_timing(fbi, var);
