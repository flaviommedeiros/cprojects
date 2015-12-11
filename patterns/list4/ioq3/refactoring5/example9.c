#ifdef MISSIONPACK
if ( gametype == GT_OBELISK || gametype == GT_HARVESTER) {
		//
		switch(BotTeam(bs)) {
			case TEAM_RED: memcpy(&bs->teamgoal, &redobelisk, sizeof(bot_goal_t)); break;
			case TEAM_BLUE: memcpy(&bs->teamgoal, &blueobelisk, sizeof(bot_goal_t)); break;
			default: return;
		}
	}
	else
#endif
		if (gametype == GT_CTF
#ifdef MISSIONPACK
			|| gametype == GT_1FCTF
#endif
			) {
		//
		switch(BotTeam(bs)) {
			case TEAM_RED: memcpy(&bs->teamgoal, &ctf_redflag, sizeof(bot_goal_t)); break;
			case TEAM_BLUE: memcpy(&bs->teamgoal, &ctf_blueflag, sizeof(bot_goal_t)); break;
			default: return;
		}
	}
	else {
		return;
	}
