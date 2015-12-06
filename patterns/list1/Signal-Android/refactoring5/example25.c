#ifndef OPENSSL_NO_DES
if (strcmp(*argv,"des") == 0)
			{
			doit[D_CBC_DES]=1;
			doit[D_EDE3_DES]=1;
			}
		else
#endif
#ifndef OPENSSL_NO_AES
			if (strcmp(*argv,"aes") == 0)
			{
			doit[D_CBC_128_AES]=1;
			doit[D_CBC_192_AES]=1;
			doit[D_CBC_256_AES]=1;
			}
		else if (strcmp(*argv,"ghash") == 0)
			{
			doit[D_GHASH]=1;
			}
		else
#endif
#ifndef OPENSSL_NO_CAMELLIA
			if (strcmp(*argv,"camellia") == 0)
			{
			doit[D_CBC_128_CML]=1;
			doit[D_CBC_192_CML]=1;
			doit[D_CBC_256_CML]=1;
			}
		else
#endif
#ifndef OPENSSL_NO_RSA
			if (strcmp(*argv,"rsa") == 0)
			{
			rsa_doit[R_RSA_512]=1;
			rsa_doit[R_RSA_1024]=1;
			rsa_doit[R_RSA_2048]=1;
			rsa_doit[R_RSA_4096]=1;
			}
		else
#endif
#ifndef OPENSSL_NO_DSA
			if (strcmp(*argv,"dsa") == 0)
			{
			dsa_doit[R_DSA_512]=1;
			dsa_doit[R_DSA_1024]=1;
			dsa_doit[R_DSA_2048]=1;
			}
		else
#endif
#ifndef OPENSSL_NO_ECDSA
		     if (strcmp(*argv,"ecdsap160") == 0) ecdsa_doit[R_EC_P160]=2;
		else if (strcmp(*argv,"ecdsap192") == 0) ecdsa_doit[R_EC_P192]=2;
		else if (strcmp(*argv,"ecdsap224") == 0) ecdsa_doit[R_EC_P224]=2;
		else if (strcmp(*argv,"ecdsap256") == 0) ecdsa_doit[R_EC_P256]=2;
		else if (strcmp(*argv,"ecdsap384") == 0) ecdsa_doit[R_EC_P384]=2;
		else if (strcmp(*argv,"ecdsap521") == 0) ecdsa_doit[R_EC_P521]=2;
		else if (strcmp(*argv,"ecdsak163") == 0) ecdsa_doit[R_EC_K163]=2;
		else if (strcmp(*argv,"ecdsak233") == 0) ecdsa_doit[R_EC_K233]=2;
		else if (strcmp(*argv,"ecdsak283") == 0) ecdsa_doit[R_EC_K283]=2;
		else if (strcmp(*argv,"ecdsak409") == 0) ecdsa_doit[R_EC_K409]=2;
		else if (strcmp(*argv,"ecdsak571") == 0) ecdsa_doit[R_EC_K571]=2;
		else if (strcmp(*argv,"ecdsab163") == 0) ecdsa_doit[R_EC_B163]=2;
		else if (strcmp(*argv,"ecdsab233") == 0) ecdsa_doit[R_EC_B233]=2;
		else if (strcmp(*argv,"ecdsab283") == 0) ecdsa_doit[R_EC_B283]=2;
		else if (strcmp(*argv,"ecdsab409") == 0) ecdsa_doit[R_EC_B409]=2;
		else if (strcmp(*argv,"ecdsab571") == 0) ecdsa_doit[R_EC_B571]=2;
		else if (strcmp(*argv,"ecdsa") == 0)
			{
			for (i=0; i < EC_NUM; i++)
				ecdsa_doit[i]=1;
			}
		else
#endif
#ifndef OPENSSL_NO_ECDH
		     if (strcmp(*argv,"ecdhp160") == 0) ecdh_doit[R_EC_P160]=2;
		else if (strcmp(*argv,"ecdhp192") == 0) ecdh_doit[R_EC_P192]=2;
		else if (strcmp(*argv,"ecdhp224") == 0) ecdh_doit[R_EC_P224]=2;
		else if (strcmp(*argv,"ecdhp256") == 0) ecdh_doit[R_EC_P256]=2;
		else if (strcmp(*argv,"ecdhp384") == 0) ecdh_doit[R_EC_P384]=2;
		else if (strcmp(*argv,"ecdhp521") == 0) ecdh_doit[R_EC_P521]=2;
		else if (strcmp(*argv,"ecdhk163") == 0) ecdh_doit[R_EC_K163]=2;
		else if (strcmp(*argv,"ecdhk233") == 0) ecdh_doit[R_EC_K233]=2;
		else if (strcmp(*argv,"ecdhk283") == 0) ecdh_doit[R_EC_K283]=2;
		else if (strcmp(*argv,"ecdhk409") == 0) ecdh_doit[R_EC_K409]=2;
		else if (strcmp(*argv,"ecdhk571") == 0) ecdh_doit[R_EC_K571]=2;
		else if (strcmp(*argv,"ecdhb163") == 0) ecdh_doit[R_EC_B163]=2;
		else if (strcmp(*argv,"ecdhb233") == 0) ecdh_doit[R_EC_B233]=2;
		else if (strcmp(*argv,"ecdhb283") == 0) ecdh_doit[R_EC_B283]=2;
		else if (strcmp(*argv,"ecdhb409") == 0) ecdh_doit[R_EC_B409]=2;
		else if (strcmp(*argv,"ecdhb571") == 0) ecdh_doit[R_EC_B571]=2;
		else if (strcmp(*argv,"ecdh") == 0)
			{
			for (i=0; i < EC_NUM; i++)
				ecdh_doit[i]=1;
			}
		else
#endif
			{
			BIO_printf(bio_err,"Error: bad option or value\n");
			BIO_printf(bio_err,"\n");
			BIO_printf(bio_err,"Available values:\n");
#ifndef OPENSSL_NO_MD2
			BIO_printf(bio_err,"md2      ");
#endif
#ifndef OPENSSL_NO_MDC2
			BIO_printf(bio_err,"mdc2     ");
#endif
#ifndef OPENSSL_NO_MD4
			BIO_printf(bio_err,"md4      ");
#endif
#ifndef OPENSSL_NO_MD5
			BIO_printf(bio_err,"md5      ");
#ifndef OPENSSL_NO_HMAC
			BIO_printf(bio_err,"hmac     ");
#endif
#endif
#ifndef OPENSSL_NO_SHA1
			BIO_printf(bio_err,"sha1     ");
#endif
#ifndef OPENSSL_NO_SHA256
			BIO_printf(bio_err,"sha256   ");
#endif
#ifndef OPENSSL_NO_SHA512
			BIO_printf(bio_err,"sha512   ");
#endif
#ifndef OPENSSL_NO_WHIRLPOOL
			BIO_printf(bio_err,"whirlpool");
#endif
#ifndef OPENSSL_NO_RIPEMD160
			BIO_printf(bio_err,"rmd160");
#endif
#if !defined(OPENSSL_NO_MD2) || !defined(OPENSSL_NO_MDC2) || \
    !defined(OPENSSL_NO_MD4) || !defined(OPENSSL_NO_MD5) || \
    !defined(OPENSSL_NO_SHA1) || !defined(OPENSSL_NO_RIPEMD160) || \
    !defined(OPENSSL_NO_WHIRLPOOL)
			BIO_printf(bio_err,"\n");
#endif

#ifndef OPENSSL_NO_IDEA
			BIO_printf(bio_err,"idea-cbc ");
#endif
#ifndef OPENSSL_NO_SEED
			BIO_printf(bio_err,"seed-cbc ");
#endif
#ifndef OPENSSL_NO_RC2
			BIO_printf(bio_err,"rc2-cbc  ");
#endif
#ifndef OPENSSL_NO_RC5
			BIO_printf(bio_err,"rc5-cbc  ");
#endif
#ifndef OPENSSL_NO_BF
			BIO_printf(bio_err,"bf-cbc");
#endif
#if !defined(OPENSSL_NO_IDEA) || !defined(OPENSSL_NO_SEED) || !defined(OPENSSL_NO_RC2) || \
    !defined(OPENSSL_NO_BF) || !defined(OPENSSL_NO_RC5)
			BIO_printf(bio_err,"\n");
#endif
#ifndef OPENSSL_NO_DES
			BIO_printf(bio_err,"des-cbc  des-ede3 ");
#endif
#ifndef OPENSSL_NO_AES
			BIO_printf(bio_err,"aes-128-cbc aes-192-cbc aes-256-cbc ");
			BIO_printf(bio_err,"aes-128-ige aes-192-ige aes-256-ige ");
#endif
#ifndef OPENSSL_NO_CAMELLIA
			BIO_printf(bio_err,"\n");
			BIO_printf(bio_err,"camellia-128-cbc camellia-192-cbc camellia-256-cbc ");
#endif
#ifndef OPENSSL_NO_RC4
			BIO_printf(bio_err,"rc4");
#endif
			BIO_printf(bio_err,"\n");

#ifndef OPENSSL_NO_RSA
			BIO_printf(bio_err,"rsa512   rsa1024  rsa2048  rsa4096\n");
#endif

#ifndef OPENSSL_NO_DSA
			BIO_printf(bio_err,"dsa512   dsa1024  dsa2048\n");
#endif
#ifndef OPENSSL_NO_ECDSA
			BIO_printf(bio_err,"ecdsap160 ecdsap192 ecdsap224 ecdsap256 ecdsap384 ecdsap521\n");
			BIO_printf(bio_err,"ecdsak163 ecdsak233 ecdsak283 ecdsak409 ecdsak571\n");
			BIO_printf(bio_err,"ecdsab163 ecdsab233 ecdsab283 ecdsab409 ecdsab571\n");
			BIO_printf(bio_err,"ecdsa\n");
#endif
#ifndef OPENSSL_NO_ECDH
			BIO_printf(bio_err,"ecdhp160  ecdhp192  ecdhp224  ecdhp256  ecdhp384  ecdhp521\n");
			BIO_printf(bio_err,"ecdhk163  ecdhk233  ecdhk283  ecdhk409  ecdhk571\n");
			BIO_printf(bio_err,"ecdhb163  ecdhb233  ecdhb283  ecdhb409  ecdhb571\n");
			BIO_printf(bio_err,"ecdh\n");
#endif

#ifndef OPENSSL_NO_IDEA
			BIO_printf(bio_err,"idea     ");
#endif
#ifndef OPENSSL_NO_SEED
			BIO_printf(bio_err,"seed     ");
#endif
#ifndef OPENSSL_NO_RC2
			BIO_printf(bio_err,"rc2      ");
#endif
#ifndef OPENSSL_NO_DES
			BIO_printf(bio_err,"des      ");
#endif
#ifndef OPENSSL_NO_AES
			BIO_printf(bio_err,"aes      ");
#endif
#ifndef OPENSSL_NO_CAMELLIA
			BIO_printf(bio_err,"camellia ");
#endif
#ifndef OPENSSL_NO_RSA
			BIO_printf(bio_err,"rsa      ");
#endif
#ifndef OPENSSL_NO_BF
			BIO_printf(bio_err,"blowfish");
#endif
#if !defined(OPENSSL_NO_IDEA) || !defined(OPENSSL_NO_SEED) || \
    !defined(OPENSSL_NO_RC2) || !defined(OPENSSL_NO_DES) || \
    !defined(OPENSSL_NO_RSA) || !defined(OPENSSL_NO_BF) || \
    !defined(OPENSSL_NO_AES) || !defined(OPENSSL_NO_CAMELLIA)
			BIO_printf(bio_err,"\n");
#endif

			BIO_printf(bio_err,"\n");
			BIO_printf(bio_err,"Available options:\n");
#if defined(TIMES) || defined(USE_TOD)
			BIO_printf(bio_err,"-elapsed        measure time in real time instead of CPU user time.\n");
#endif
#ifndef OPENSSL_NO_ENGINE
			BIO_printf(bio_err,"-engine e       use engine e, possibly a hardware device.\n");
#endif
			BIO_printf(bio_err,"-evp e          use EVP e.\n");
			BIO_printf(bio_err,"-decrypt        time decryption instead of encryption (only EVP).\n");
			BIO_printf(bio_err,"-mr             produce machine readable output.\n");
#ifndef NO_FORK
			BIO_printf(bio_err,"-multi n        run n benchmarks in parallel.\n");
#endif
			goto end;
			}
