switch (goal->malgo->algo)
		{
#ifdef USE_SCRYPT
			case POW_SCRYPT:
				root = api_add_const(root, "Hash Method", SCRYPTSTR, false);
				break;
#endif
#ifdef USE_SHA256D
			case POW_SHA256D:
				root = api_add_const(root, "Hash Method", SHA256STR, false);
				break;
#endif
			default:
				root = api_add_const(root, "Hash Method", goal->malgo->name, false);
				break;
		}
