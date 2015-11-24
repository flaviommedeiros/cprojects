#ifndef OPENSSL_NO_DH
if (alg_k & (SSL_kEDH|SSL_kDHr|SSL_kDHd))
			    {
			    if (dh == NULL
				|| DH_size(dh)*8 > SSL_C_EXPORT_PKEYLENGTH(s->s3->tmp.new_cipher))
				{
				SSLerr(SSL_F_SSL3_CHECK_CERT_AND_ALGORITHM,SSL_R_MISSING_EXPORT_TMP_DH_KEY);
				goto f_err;
				}
			}
		else
#endif
			{
			SSLerr(SSL_F_SSL3_CHECK_CERT_AND_ALGORITHM,SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE);
			goto f_err;
			}
