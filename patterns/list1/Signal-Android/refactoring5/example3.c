#ifndef OPENSSL_NO_RSA
if (EVP_PKEY_base_id(tpubkey) == EVP_PKEY_RSA)
			BN_print(out,tpubkey->pkey.rsa->n);
		else
#endif
			fprintf(stdout,"Wrong Algorithm type");
