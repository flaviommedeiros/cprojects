if (gametype == GT_CTF
#ifdef MISSIONPACK
		|| gametype == GT_1FCTF
#endif
		) {
		if (BotTeam(bs) == TEAM_RED) context |= CONTEXT_CTFREDTEAM;
		else context |= CONTEXT_CTFBLUETEAM;
	}
#ifdef MISSIONPACK
	else if (gametype == GT_OBELISK) {
		if (BotTeam(bs) == TEAM_RED) context |= CONTEXT_OBELISKREDTEAM;
		else context |= CONTEXT_OBELISKBLUETEAM;
	}
	else if (gametype == GT_HARVESTER) {
		if (BotTeam(bs) == TEAM_RED) context |= CONTEXT_HARVESTERREDTEAM;
		else context |= CONTEXT_HARVESTERBLUETEAM;
	}
