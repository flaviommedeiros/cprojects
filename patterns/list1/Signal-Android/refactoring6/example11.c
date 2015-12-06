if ((s->verify_mode != SSL_VERIFY_NONE) && (i <= 0)
#ifndef OPENSSL_NO_KRB5
	    && !((s->s3->tmp.new_cipher->algorithm_mkey & SSL_kKRB5) &&
		 (s->s3->tmp.new_cipher->algorithm_auth & SSL_aKRB5))
#endif /* OPENSSL_NO_KRB5 */
		)
		{
		al=ssl_verify_alarm_type(s->verify_result);
		SSLerr(SSL_F_SSL3_GET_SERVER_CERTIFICATE,SSL_R_CERTIFICATE_VERIFY_FAILED);
		goto f_err; 
		}
