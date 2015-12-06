if ((s->session == NULL) ||
			(s->session->ssl_version != s->version) ||
#ifdef OPENSSL_NO_TLSEXT
			!sess->session_id_length ||
#else
			(!sess->session_id_length && !sess->tlsext_tick) ||
#endif
			(s->session->not_resumable))
			{
		        if (!s->session_creation_enabled)
				{
				ssl3_send_alert(s,SSL3_AL_FATAL,SSL_AD_HANDSHAKE_FAILURE);
				SSLerr(SSL_F_DTLS1_CLIENT_HELLO,SSL_R_SESSION_MAY_NOT_BE_CREATED);
				goto err;
				}
			if (!ssl_get_new_session(s,0))
				goto err;
			}
