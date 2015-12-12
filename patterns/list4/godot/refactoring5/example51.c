#ifndef OPENSSL_NO_PSK
if (type & SSL_kPSK)
				{
				/* reserve size for record length and PSK identity hint*/
				n+=2+strlen(s->ctx->psk_identity_hint);
				}
			else
#endif /* !OPENSSL_NO_PSK */
			{
			al=SSL_AD_HANDSHAKE_FAILURE;
			SSLerr(SSL_F_DTLS1_SEND_SERVER_KEY_EXCHANGE,SSL_R_UNKNOWN_KEY_EXCHANGE_TYPE);
			goto f_err;
			}
