if (targ->client && attacker && attacker->client
#ifndef DEBUG_STATS
		    && attacker->client->sess.sessionTeam != targ->client->sess.sessionTeam
#endif
		    )
		{
			G_addStatsHeadShot(attacker, mod);
			attacker->client->ps.persistant[PERS_HEADSHOTS]++;
		}
