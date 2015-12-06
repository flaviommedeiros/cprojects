switch (work_mining_algorithm(work)->algo)
		{
#ifdef USE_SCRYPT
			case POW_SCRYPT:
				func = scanhash_scrypt;
				break;
#endif
#ifdef USE_SHA256D
			case POW_SHA256D:
				if (work->nonce_diff >= 1.)
					func = sha256_funcs[opt_algo];
				break;
#endif
			default:
				break;
		}
