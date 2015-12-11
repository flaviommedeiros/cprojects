if ( gametype == GT_CTF
#ifdef MISSIONPACK
		|| gametype == GT_1FCTF
#endif
		) {
		BotVoiceChat_GetFlag(bs, client, mode);
		return;
	}
