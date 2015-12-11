#ifdef MISSIONPACK
if( g_gametype.integer == GT_1FCTF ) {
		PrintMsg (NULL, "%s" S_COLOR_WHITE " got the flag!\n", other->client->pers.netname );

		cl->ps.powerups[PW_NEUTRALFLAG] = INT_MAX; // flags never expire

		if( team == TEAM_RED ) {
			Team_SetFlagStatus( TEAM_FREE, FLAG_TAKEN_RED );
		}
		else {
			Team_SetFlagStatus( TEAM_FREE, FLAG_TAKEN_BLUE );
		}
	}
	else{
#endif
		PrintMsg (NULL, "%s" S_COLOR_WHITE " got the %s flag!\n",
			other->client->pers.netname, TeamName(team));

		if (team == TEAM_RED)
			cl->ps.powerups[PW_REDFLAG] = INT_MAX; // flags never expire
		else
			cl->ps.powerups[PW_BLUEFLAG] = INT_MAX; // flags never expire

		Team_SetFlagStatus( team, FLAG_TAKEN );
#ifdef MISSIONPACK
	}
