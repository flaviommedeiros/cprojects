#ifndef OPENSSL_NO_PSK
if (type & SSL_kPSK)
				{
				/* reserve size for record length and PSK identity hint*/
				n+=2+strlen(s->ctx->psk_identity_hint);
				}
			else
#endif /* !OPENSSL_NO_PSK */
#ifndef OPENSSL_NO_SRP
		if (type & SSL_kSRP)
			{
			if ((s->srp_ctx.N == NULL) ||
				(s->srp_ctx.g == NULL) ||
				(s->srp_ctx.s == NULL) ||
				(s->srp_ctx.B == NULL))
				{
				SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,SSL_R_MISSING_SRP_PARAM);
				goto err;
				}
			r[0]=s->srp_ctx.N;
			r[1]=s->srp_ctx.g;
			r[2]=s->srp_ctx.s;
			r[3]=s->srp_ctx.B;
			}
		else 
#endif
			{
			al=SSL_AD_HANDSHAKE_FAILURE;
			SSLerr(SSL_F_SSL3_SEND_SERVER_KEY_EXCHANGE,SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE);
			goto f_err;
			}
