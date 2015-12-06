if (cg.snap->ps.powerups[PW_BLACKOUT] == 0
#if FEATURE_MULTIVIEW
	         || cg.mvTotalClients > 0
#endif
	         )
	{
		trap_Cvar_Set("ui_blackout", "0");
	}
