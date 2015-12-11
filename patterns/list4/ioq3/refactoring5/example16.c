#ifdef MISSIONPACK
if( g_gametype.integer == GT_1FCTF ) {
		enemy_flag = PW_NEUTRALFLAG;
	}
	else {
#endif
	if (cl->sess.sessionTeam == TEAM_RED) {
		enemy_flag = PW_BLUEFLAG;
	} else {
		enemy_flag = PW_REDFLAG;
	}

	if ( ent->flags & FL_DROPPED_ITEM ) {
		// hey, it's not home.  return it by teleporting it back
		PrintMsg( NULL, "%s" S_COLOR_WHITE " returned the %s flag!\n", 
			cl->pers.netname, TeamName(team));
		AddScore(other, ent->r.currentOrigin, CTF_RECOVERY_BONUS);
		other->client->pers.teamState.flagrecovery++;
		other->client->pers.teamState.lastreturnedflag = level.time;
		//ResetFlag will remove this entity!  We must return zero
		Team_ReturnFlagSound(Team_ResetFlag(team), team);
		return 0;
	}
#ifdef MISSIONPACK
	}
