if (
		gametype != GT_CTF
#ifdef MISSIONPACK
		&& gametype != GT_1FCTF
#endif
		) {
		return;
	}
