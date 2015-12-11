#ifdef MISSIONPACK
if (gametype == GT_CTF || gametype == GT_1FCTF)
#else
	if (gametype == GT_CTF)
#endif
	{
		if (BotTeam(bs) == TEAM_RED)
			goal = &ctf_redflag;
		else
			goal = &ctf_blueflag;
	}
#ifdef MISSIONPACK
	else {
		if (BotTeam(bs) == TEAM_RED)
			goal = &redobelisk;
		else
			goal = &blueobelisk;
	}
