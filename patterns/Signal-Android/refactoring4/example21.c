#ifdef OPENSSL_FIPS
if (!FIPS_mode())
#endif
		CRYPTO_w_lock(CRYPTO_LOCK_RAND);
