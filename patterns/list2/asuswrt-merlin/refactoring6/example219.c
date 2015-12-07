if ((digest->code != CHAP_MD5)
#ifdef CHAPMS
	&& (digest->code != CHAP_MICROSOFT)
	&& (digest->code != CHAP_MICROSOFT_V2)
#endif
	) {
	error("RADIUS: Challenge type %u unsupported", digest->code);
	return 0;
    }
