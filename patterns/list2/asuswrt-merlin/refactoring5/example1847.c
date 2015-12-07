#ifdef DEBUGMPPEKEY
if (mschap_challenge && strlen(mschap_challenge) == 8)
		memcpy(challenge, mschap_challenge, 8);
	else
#endif
		random_bytes(challenge, 8);
