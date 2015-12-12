#ifdef CONFIG_FB_PXA_OVERLAY
if (!(fbi->overlay[0].usage || fbi->overlay[1].usage))
#endif
			set_ctrlr_state(fbi, C_DISABLE_CLKCHANGE);
