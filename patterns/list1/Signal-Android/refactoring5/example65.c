#ifndef OPENSSL_NO_SHA512
if (EC_KEY_get_nonce_from_hash(eckey))
			{
				if (!BN_generate_dsa_nonce(
					k, order,
					EC_KEY_get0_private_key(eckey),
					dgst, dlen, ctx))
					{
					ECDSAerr(ECDSA_F_ECDSA_SIGN_SETUP,
						 ECDSA_R_RANDOM_NUMBER_GENERATION_FAILED);
					goto err;
					}
			}
			else
#endif
			{
				if (!BN_rand_range(k, order))
				{
					ECDSAerr(ECDSA_F_ECDSA_SIGN_SETUP,
					 ECDSA_R_RANDOM_NUMBER_GENERATION_FAILED);
					goto err;
				}
			}
