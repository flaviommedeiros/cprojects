if (
#if FEATURE_MULTIVIEW
	    cg.mvTotalClients < 1 &&
#endif
	    cg_drawWeaponIconFlash.integer == 0)
	{
		CG_DrawPlayerWeaponIcon(&rect, qtrue, ITEM_ALIGN_RIGHT, &colorWhite);
	}
	else
	{
		int ws =
#if FEATURE_MULTIVIEW
		    (cg.mvTotalClients > 0) ? cgs.clientinfo[cg.snap->ps.clientNum].weaponState :
#endif
		    BG_simpleWeaponState(cg.snap->ps.weaponstate);

		CG_DrawPlayerWeaponIcon(&rect, (ws != WSTATE_IDLE), ITEM_ALIGN_RIGHT, ((ws == WSTATE_SWITCH || ws == WSTATE_RELOAD) ? &colorYellow : (ws == WSTATE_FIRE) ? &colorRed : &colorWhite));
	}
