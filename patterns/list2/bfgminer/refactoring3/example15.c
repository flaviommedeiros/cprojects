switch (malgo->algo)
	{
#ifdef USE_SCRYPT
		case POW_SCRYPT:
			return 1./0x10000;
#endif
#ifdef USE_SHA256D
		case POW_SHA256D:
			return 1.;
#endif
		default:
			return -1.;
	}
