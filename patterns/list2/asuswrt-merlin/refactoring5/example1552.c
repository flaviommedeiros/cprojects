#ifdef DEBUGMPPEKEY
if (mschap_challenge && strlen(mschap_challenge) == 16)
		memcpy(challenge, mschap_challenge, 16);
	else
#endif
		random_bytes(challenge, 16);
