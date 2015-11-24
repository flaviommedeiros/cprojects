#ifndef OPENSSL_NO_RSA
if (pkey->type == EVP_PKEY_RSA)
					BN_print(STDout,pkey->pkey.rsa->n);
				else
#endif
#ifndef OPENSSL_NO_DSA
				if (pkey->type == EVP_PKEY_DSA)
					BN_print(STDout,pkey->pkey.dsa->pub_key);
				else
#endif
					BIO_printf(STDout,"Wrong Algorithm type");
