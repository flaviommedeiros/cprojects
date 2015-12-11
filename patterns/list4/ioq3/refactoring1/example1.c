if (gametype == GT_CTF) {
				switch(state->eventParm) {
					case GTS_RED_CAPTURE:
						bs->blueflagstatus = 0;
						bs->redflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break; //see BotMatch_CTF
					case GTS_BLUE_CAPTURE:
						bs->blueflagstatus = 0;
						bs->redflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break; //see BotMatch_CTF
					case GTS_RED_RETURN:
						//blue flag is returned
						bs->blueflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_BLUE_RETURN:
						//red flag is returned
						bs->redflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_RED_TAKEN:
						//blue flag is taken
						bs->blueflagstatus = 1;
						bs->flagstatuschanged = qtrue;
						break; //see BotMatch_CTF
					case GTS_BLUE_TAKEN:
						//red flag is taken
						bs->redflagstatus = 1;
						bs->flagstatuschanged = qtrue;
						break; //see BotMatch_CTF
				}
			}
#ifdef MISSIONPACK
			else if (gametype == GT_1FCTF) {
				switch(state->eventParm) {
					case GTS_RED_CAPTURE:
						bs->neutralflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_BLUE_CAPTURE:
						bs->neutralflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_RED_RETURN:
						//flag has returned
						bs->neutralflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_BLUE_RETURN:
						//flag has returned
						bs->neutralflagstatus = 0;
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_RED_TAKEN:
						bs->neutralflagstatus = BotTeam(bs) == TEAM_RED ? 2 : 1; //FIXME: check Team_TakeFlagSound in g_team.c
						bs->flagstatuschanged = qtrue;
						break;
					case GTS_BLUE_TAKEN:
						bs->neutralflagstatus = BotTeam(bs) == TEAM_BLUE ? 2 : 1; //FIXME: check Team_TakeFlagSound in g_team.c
						bs->flagstatuschanged = qtrue;
						break;
				}
			}
#endif
