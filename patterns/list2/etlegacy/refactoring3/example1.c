switch (dpent->spawnflags)
	{
	case DP_PAUSEINFO:
	{
		if (level.match_pause > PAUSE_UNPAUSING)
		{
			int cSeconds = match_timeoutlength.integer * 1000 - (level.time - dpent->timestamp);

			if (cSeconds > 1000)
			{
				AP(va("cp \"^3Match resuming in ^1%d^3 seconds!\n\"", cSeconds / 1000));
				think_next = level.time + 15000;
				fFree      = qfalse;
			}
			else
			{
				level.match_pause = PAUSE_UNPAUSING;
				AP("print \"^3Match resuming in 10 seconds!\n\"");
				G_globalSound("sound/osp/prepare.wav");
				G_spawnPrintf(DP_UNPAUSING, level.time + 10, NULL);
			}
		}
		break;
	}

	case DP_UNPAUSING:
	{
		if (level.match_pause == PAUSE_UNPAUSING)
		{
			int cSeconds = 11 * 1000 - (level.time - dpent->timestamp);

			if (cSeconds > 1000)
			{
				AP(va("cp \"^3Match resuming in ^1%d^3 seconds!\n\"", cSeconds / 1000));
				think_next = level.time + 1000;
				fFree      = qfalse;
			}
			else
			{
				level.match_pause = PAUSE_NONE;
				G_globalSound("sound/osp/fight.wav");
				G_printFull("^1FIGHT!", NULL);
				trap_SetConfigstring(CS_LEVEL_START_TIME, va("%i", level.startTime + level.timeDelta));
				level.server_settings &= ~CV_SVS_PAUSE;
				trap_SetConfigstring(CS_SERVERTOGGLES, va("%d", level.server_settings));
			}
		}
		break;
	}

#ifdef FEATURE_MULTIVIEW
	case DP_MVSPAWN:
	{
		int       i;
		gentity_t *ent;

		for (i = 0; i < level.numConnectedClients; i++)
		{
			ent = g_entities + level.sortedClients[i];

			if (ent->client->pers.mvReferenceList == 0)
			{
				continue;
			}
			if (ent->client->sess.sessionTeam != TEAM_SPECTATOR)
			{
				continue;
			}
			G_smvRegenerateClients(ent, ent->client->pers.mvReferenceList);
		}

		break;
	}
#endif

	default:
		break;
	}
