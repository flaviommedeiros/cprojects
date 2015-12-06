if(!ENGINE_set_id(e, engine_openssl_id)
			|| !ENGINE_set_name(e, engine_openssl_name)
#ifndef TEST_ENG_OPENSSL_NO_ALGORITHMS
#ifndef OPENSSL_NO_RSA
			|| !ENGINE_set_RSA(e, RSA_get_default_method())
#endif
#ifndef OPENSSL_NO_DSA
			|| !ENGINE_set_DSA(e, DSA_get_default_method())
#endif
#ifndef OPENSSL_NO_ECDH
			|| !ENGINE_set_ECDH(e, ECDH_OpenSSL())
#endif
#ifndef OPENSSL_NO_ECDSA
			|| !ENGINE_set_ECDSA(e, ECDSA_OpenSSL())
#endif
#ifndef OPENSSL_NO_DH
			|| !ENGINE_set_DH(e, DH_get_default_method())
#endif
			|| !ENGINE_set_RAND(e, RAND_SSLeay())
#ifdef TEST_ENG_OPENSSL_RC4
			|| !ENGINE_set_ciphers(e, openssl_ciphers)
#endif
#ifdef TEST_ENG_OPENSSL_SHA
			|| !ENGINE_set_digests(e, openssl_digests)
#endif
#endif
#ifdef TEST_ENG_OPENSSL_PKEY
			|| !ENGINE_set_load_privkey_function(e, openssl_load_privkey)
#endif
			)
		return 0;
