#ifndef OPENSSL_NO_SHA512
if (dsa->flags & DSA_FLAG_NONCE_FROM_HASH)
			{
			/* If DSA_FLAG_NONCE_FROM_HASH is set then we calculate k from
			 * SHA512(private_key + H(message) + random). This protects the
			 * private key from a weak PRNG. */
			if (!BN_generate_dsa_nonce(&k, dsa->q, dsa->priv_key, dgst,
						   dlen, ctx))
				goto err;
			}
		else
#endif
			if (!BN_rand_range(&k, dsa->q)) goto err;
