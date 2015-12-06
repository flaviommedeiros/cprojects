#ifndef DEBUG_STATS
if (g_debugDamage.integer)
#endif
	{
		G_Printf("client:%i health:%i damage:%i mod:%s\n", targ->s.number, targ->health, take, modNames[mod]);
	}
