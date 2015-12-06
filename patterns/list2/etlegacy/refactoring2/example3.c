#ifndef DEBUG_STATS
if (g_developer.integer || *g_log.string || g_dedicated.integer)
#endif
	{
		G_Printf("Userinfo: %s\n", userinfo);
	}
