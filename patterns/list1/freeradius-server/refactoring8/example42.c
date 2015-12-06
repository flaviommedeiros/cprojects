static const FR_NAME_NUMBER header_names[] = {
	{ "{clear}",		PW_CLEARTEXT_PASSWORD },
	{ "{cleartext}",	PW_CLEARTEXT_PASSWORD },
	{ "{md5}",		PW_MD5_PASSWORD },
	{ "{base64_md5}",	PW_MD5_PASSWORD },
	{ "{smd5}",		PW_SMD5_PASSWORD },
	{ "{crypt}",		PW_CRYPT_PASSWORD },
#ifdef HAVE_OPENSSL_EVP_H
	/*
	 *	It'd make more sense for the headers to be
	 *	ssha2-* with SHA3 coming soon but we're at
	 *	the mercy of directory implementors.
	 */
	{ "{sha2}",		PW_SHA2_PASSWORD },
	{ "{sha224}",		PW_SHA2_PASSWORD },
	{ "{sha256}",		PW_SHA2_PASSWORD },
	{ "{sha384}",		PW_SHA2_PASSWORD },
	{ "{sha512}",		PW_SHA2_PASSWORD },
	{ "{ssha224}",		PW_SSHA2_224_PASSWORD },
	{ "{ssha256}",		PW_SSHA2_256_PASSWORD },
	{ "{ssha384}",		PW_SSHA2_384_PASSWORD },
	{ "{ssha512}",		PW_SSHA2_512_PASSWORD },
#endif
	{ "{sha}",		PW_SHA_PASSWORD },
	{ "{ssha}",		PW_SSHA_PASSWORD },
	{ "{md4}",		PW_NT_PASSWORD },
	{ "{nt}",		PW_NT_PASSWORD },
	{ "{nthash}",		PW_NT_PASSWORD },
	{ "{x-nthash}",		PW_NT_PASSWORD },
	{ "{ns-mta-md5}",	PW_NS_MTA_MD5_PASSWORD },
	{ "{x- orcllmv}",	PW_LM_PASSWORD },
	{ "{X- orclntv}",	PW_NT_PASSWORD },
	{ NULL, 0 }
};
