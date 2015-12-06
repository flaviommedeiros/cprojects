#ifndef OPENSSL_NO_RSA
if (pkey->type == EVP_PKEY_RSA
					&& TLS1_get_version(s) < TLS1_2_VERSION)
				{
				q=md_buf;
				j=0;
				for (num=2; num > 0; num--)
					{
					EVP_MD_CTX_set_flags(&md_ctx,
						EVP_MD_CTX_FLAG_NON_FIPS_ALLOW);
					EVP_DigestInit_ex(&md_ctx,(num == 2)
						?s->ctx->md5:s->ctx->sha1, NULL);
					EVP_DigestUpdate(&md_ctx,&(s->s3->client_random[0]),SSL3_RANDOM_SIZE);
					EVP_DigestUpdate(&md_ctx,&(s->s3->server_random[0]),SSL3_RANDOM_SIZE);
					EVP_DigestUpdate(&md_ctx,&(d[4]),n);
					EVP_DigestFinal_ex(&md_ctx,q,
						(unsigned int *)&i);
					q+=i;
					j+=i;
					}
				if (RSA_sign(NID_md5_sha1, md_buf, j,
					&(p[2]), &u, pkey->pkey.rsa) <= 0)
					{
					SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,ERR_LIB_RSA);
					goto err;
					}
				s2n(u,p);
				n+=u+2;
				}
			else
#endif /* OPENSSL_NO_RSA */
			if (md)
				{
				/* For TLS1.2 and later send signature
				 * algorithm */
				if (TLS1_get_version(s) >= TLS1_2_VERSION)
					{
					if (!tls12_get_sigandhash(p, pkey, md))
						{
						/* Should never happen */
						al=SSL_AD_INTERNAL_ERROR;
						SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,ERR_R_INTERNAL_ERROR);
						goto f_err;
						}
					p+=2;
					}
#ifdef SSL_DEBUG
				fprintf(stderr, "Using hash %s\n",
							EVP_MD_name(md));
#endif
				EVP_SignInit_ex(&md_ctx, md, NULL);
				EVP_SignUpdate(&md_ctx,&(s->s3->client_random[0]),SSL3_RANDOM_SIZE);
				EVP_SignUpdate(&md_ctx,&(s->s3->server_random[0]),SSL3_RANDOM_SIZE);
				EVP_SignUpdate(&md_ctx,&(d[4]),n);
				if (!EVP_SignFinal(&md_ctx,&(p[2]),
					(unsigned int *)&i,pkey))
					{
					SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,ERR_LIB_EVP);
					goto err;
					}
				s2n(i,p);
				n+=i+2;
				if (TLS1_get_version(s) >= TLS1_2_VERSION)
					n+= 2;
				}
			else
				{
				/* Is this error check actually needed? */
				al=SSL_AD_HANDSHAKE_FAILURE;
				SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,SSL_R_UNKNOWN_PKEY_TYPE);
				goto f_err;
				}
