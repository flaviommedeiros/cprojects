#ifndef OPENSSL_NO_RSA
if (pkey->type == EVP_PKEY_RSA)
		{
		i=RSA_verify(NID_md5_sha1, s->s3->tmp.cert_verify_md,
			MD5_DIGEST_LENGTH+SHA_DIGEST_LENGTH, p, i, 
							pkey->pkey.rsa);
		if (i < 0)
			{
			al=SSL_AD_DECRYPT_ERROR;
			SSLerr(SSL_F_SSL3_GET_CERT_VERIFY,SSL_R_BAD_RSA_DECRYPT);
			goto f_err;
			}
		if (i == 0)
			{
			al=SSL_AD_DECRYPT_ERROR;
			SSLerr(SSL_F_SSL3_GET_CERT_VERIFY,SSL_R_BAD_RSA_SIGNATURE);
			goto f_err;
			}
		}
	else
#endif
#ifndef OPENSSL_NO_DSA
		if (pkey->type == EVP_PKEY_DSA)
		{
		j=DSA_verify(pkey->save_type,
			&(s->s3->tmp.cert_verify_md[MD5_DIGEST_LENGTH]),
			SHA_DIGEST_LENGTH,p,i,pkey->pkey.dsa);
		if (j <= 0)
			{
			/* bad signature */
			al=SSL_AD_DECRYPT_ERROR;
			SSLerr(SSL_F_SSL3_GET_CERT_VERIFY,SSL_R_BAD_DSA_SIGNATURE);
			goto f_err;
			}
		}
	else
#endif
#ifndef OPENSSL_NO_ECDSA
		if (pkey->type == EVP_PKEY_EC)
		{
		j=ECDSA_verify(pkey->save_type,
			&(s->s3->tmp.cert_verify_md[MD5_DIGEST_LENGTH]),
			SHA_DIGEST_LENGTH,p,i,pkey->pkey.ec);
		if (j <= 0)
			{
			/* bad signature */
			al=SSL_AD_DECRYPT_ERROR;
			SSLerr(SSL_F_SSL3_GET_CERT_VERIFY,
			    SSL_R_BAD_ECDSA_SIGNATURE);
			goto f_err;
			}
		}
	else
#endif
	if (pkey->type == NID_id_GostR3410_94 || pkey->type == NID_id_GostR3410_2001)
		{   unsigned char signature[64];
			int idx;
			EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new(pkey,NULL);
			EVP_PKEY_verify_init(pctx);
			if (i!=64) {
				fprintf(stderr,"GOST signature length is %d",i);
			}	
			for (idx=0;idx<64;idx++) {
				signature[63-idx]=p[idx];
			}	
			j=EVP_PKEY_verify(pctx,signature,64,s->s3->tmp.cert_verify_md,32);
			EVP_PKEY_CTX_free(pctx);
			if (j<=0) 
				{
				al=SSL_AD_DECRYPT_ERROR;
				SSLerr(SSL_F_SSL3_GET_CERT_VERIFY,
					SSL_R_BAD_ECDSA_SIGNATURE);
				goto f_err;
				}	
		}
	else	
		{
		SSLerr(SSL_F_SSL3_GET_CERT_VERIFY,ERR_R_INTERNAL_ERROR);
		al=SSL_AD_UNSUPPORTED_CERTIFICATE;
		goto f_err;
		}
