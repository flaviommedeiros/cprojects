#ifdef OPENSSL_FIPS
if (curr->active && (!FIPS_mode() || curr->cipher->algo_strength & SSL_FIPS))
#else
		if (curr->active)
#endif
			{
			sk_SSL_CIPHER_push(cipherstack, curr->cipher);
#ifdef CIPHER_DEBUG
			printf("<%s>\n",curr->cipher->name);
#endif
			}
