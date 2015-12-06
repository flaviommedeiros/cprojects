if (
#if FEATURE_MULTIVIEW
		    cg.mvTotalClients < 1 &&
#endif
		    cg.snap->ps.powerups[PW_BLACKOUT] > 0)
		{
			trap_Cvar_Set("ui_blackout", va("%d", cg.snap->ps.powerups[PW_BLACKOUT]));
		}
