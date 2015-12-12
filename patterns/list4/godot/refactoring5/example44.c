#ifndef OPENSSL_NO_RSA
if (pkey->type == EVP_PKEY_RSA)
			{
			s->method->ssl3_enc->cert_verify_mac(s,
				NID_md5,
				&(data[0]));
			if (RSA_sign(NID_md5_sha1, data,
					 MD5_DIGEST_LENGTH+SHA_DIGEST_LENGTH,
					&(p[2]), &u, pkey->pkey.rsa) <= 0 )
				{
				SSLerr(SSL_F_DTLS1_SEND_CLIENT_VERIFY,ERR_R_RSA_LIB);
				goto err;
				}
			s2n(u,p);
			n=u+2;
			}
		else
#endif
#ifndef OPENSSL_NO_DSA
			if (pkey->type == EVP_PKEY_DSA)
			{
			if (!DSA_sign(pkey->save_type,
				&(data[MD5_DIGEST_LENGTH]),
				SHA_DIGEST_LENGTH,&(p[2]),
				(unsigned int *)&j,pkey->pkey.dsa))
				{
				SSLerr(SSL_F_DTLS1_SEND_CLIENT_VERIFY,ERR_R_DSA_LIB);
				goto err;
				}
			s2n(j,p);
			n=j+2;
			}
		else
#endif
#ifndef OPENSSL_NO_ECDSA
			if (pkey->type == EVP_PKEY_EC)
			{
			if (!ECDSA_sign(pkey->save_type,
				&(data[MD5_DIGEST_LENGTH]),
				SHA_DIGEST_LENGTH,&(p[2]),
				(unsigned int *)&j,pkey->pkey.ec))
				{
				SSLerr(SSL_F_DTLS1_SEND_CLIENT_VERIFY,
				    ERR_R_ECDSA_LIB);
				goto err;
				}
			s2n(j,p);
			n=j+2;
			}
		else
#endif
			{
			SSLerr(SSL_F_DTLS1_SEND_CLIENT_VERIFY,ERR_R_INTERNAL_ERROR);
			goto err;
			}
