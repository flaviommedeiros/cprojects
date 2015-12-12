static const
struct public_key_algorithm *x509_public_key_algorithms[PKEY_ALGO__LAST] = {
	[PKEY_ALGO_DSA]		= NULL,
#if defined(CONFIG_PUBLIC_KEY_ALGO_RSA) || \
	defined(CONFIG_PUBLIC_KEY_ALGO_RSA_MODULE)
	[PKEY_ALGO_RSA]		= &RSA_public_key_algorithm,
#endif
};
