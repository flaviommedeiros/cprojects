if (
#ifndef DEBUG_STATS
	    g_gamestate.integer != GS_PLAYING ||
#endif
	    mod == MOD_SWITCHTEAM ||
	    (g_gametype.integer >= GT_WOLF && (targ->client->ps.pm_flags & PMF_LIMBO)) || // FIXME: inspect - this is a bit odd by gametype
	    (g_gametype.integer < GT_WOLF && (targ->s.eFlags == EF_DEAD || targ->client->ps.pm_type == PM_DEAD)))
	{
		return;
	}
