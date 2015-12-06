if (((cg.snap->ps.pm_flags & PMF_FOLLOW) || cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR)
#if FEATURE_MULTIVIEW
	    || cg.mvTotalClients > 0
#endif
	    )
	{
		trap_SendConsoleCommand("followprev");
		return;
	}
