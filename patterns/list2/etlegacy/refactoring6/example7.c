if (snap->ps.pm_flags & PMF_LIMBO /*|| snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR*/
#if FEATURE_MULTIVIEW
	    || cg.mvTotalClients > 0
#endif
	    )
	{
		CG_DrawExpandedAutoMap();
		return;
	}
