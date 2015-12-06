switch (malgo->algo)
	{
#ifdef USE_SCRYPT
		case POW_SCRYPT:
			return ((!info) || dualminer_is_scrypt(info)) ? (1./0x10000) : -1.;
#endif
#ifdef USE_SHA256D
		case POW_SHA256D:
			return (info && dualminer_is_scrypt(info)) ? -1. : 1.;
#endif
		default:
			return -1.;
	}
