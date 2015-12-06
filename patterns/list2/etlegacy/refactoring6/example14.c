if (
#ifdef FEATURE_MULTIVIEW
		    cg.mvTotalClients < 1 &&
#endif
		    cg.snap->ps.persistant[PERS_TEAM] == TEAM_SPECTATOR)
		{
			Pri("You must be a player or following a player to use +stats\n");
			return;
		}
