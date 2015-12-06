switch (s->state)
			{
		case SSL_ST_RENEGOTIATE:
			s->renegotiate=1;
			/* s->state=SSL_ST_ACCEPT; */

		case SSL_ST_BEFORE:
		case SSL_ST_ACCEPT:
		case SSL_ST_BEFORE|SSL_ST_ACCEPT:
		case SSL_ST_OK|SSL_ST_ACCEPT:

			s->server=1;
			if (cb != NULL) cb(s,SSL_CB_HANDSHAKE_START,1);

			if ((s->version & 0xff00) != (DTLS1_VERSION & 0xff00))
				{
				SSLerr(SSL_F_DTLS1_ACCEPT, ERR_R_INTERNAL_ERROR);
				return -1;
				}
			s->type=SSL_ST_ACCEPT;

			if (s->init_buf == NULL)
				{
				if ((buf=BUF_MEM_new()) == NULL)
					{
					ret= -1;
					goto end;
					}
				if (!BUF_MEM_grow(buf,SSL3_RT_MAX_PLAIN_LENGTH))
					{
					BUF_MEM_free(buf);
					ret= -1;
					goto end;
					}
				s->init_buf=buf;
				}

			if (!ssl3_setup_buffers(s))
				{
				ret= -1;
				goto end;
				}

			s->init_num=0;
			s->d1->change_cipher_spec_ok = 0;
			/* Should have been reset by ssl3_get_finished, too. */
			s->s3->change_cipher_spec = 0;

			if (s->state != SSL_ST_RENEGOTIATE)
				{
				/* Ok, we now need to push on a buffering BIO so that
				 * the output is sent in a way that TCP likes :-)
				 * ...but not with SCTP :-)
				 */
#ifndef OPENSSL_NO_SCTP
				if (!BIO_dgram_is_sctp(SSL_get_wbio(s)))
#endif
					if (!ssl_init_wbio_buffer(s,1)) { ret= -1; goto end; }

				ssl3_init_finished_mac(s);
				s->state=SSL3_ST_SR_CLNT_HELLO_A;
				s->ctx->stats.sess_accept++;
				}
			else
				{
				/* s->state == SSL_ST_RENEGOTIATE,
				 * we will just send a HelloRequest */
				s->ctx->stats.sess_accept_renegotiate++;
				s->state=SSL3_ST_SW_HELLO_REQ_A;
				}

			break;

		case SSL3_ST_SW_HELLO_REQ_A:
		case SSL3_ST_SW_HELLO_REQ_B:

			s->shutdown=0;
			dtls1_clear_record_buffer(s);
			dtls1_start_timer(s);
			ret=dtls1_send_hello_request(s);
			if (ret <= 0) goto end;
			s->s3->tmp.next_state=SSL3_ST_SR_CLNT_HELLO_A;
			s->state=SSL3_ST_SW_FLUSH;
			s->init_num=0;

			ssl3_init_finished_mac(s);
			break;

		case SSL3_ST_SW_HELLO_REQ_C:
			s->state=SSL_ST_OK;
			break;

		case SSL3_ST_SR_CLNT_HELLO_A:
		case SSL3_ST_SR_CLNT_HELLO_B:
		case SSL3_ST_SR_CLNT_HELLO_C:

			s->shutdown=0;
			ret=ssl3_get_client_hello(s);
			if (ret <= 0) goto end;
			dtls1_stop_timer(s);

			if (ret == 1 && (SSL_get_options(s) & SSL_OP_COOKIE_EXCHANGE))
				s->state = DTLS1_ST_SW_HELLO_VERIFY_REQUEST_A;
			else
				s->state = SSL3_ST_SW_SRVR_HELLO_A;

			s->init_num=0;

			/* Reflect ClientHello sequence to remain stateless while listening */
			if (listen)
				{
				memcpy(s->s3->write_sequence, s->s3->read_sequence, sizeof(s->s3->write_sequence));
				}

			/* If we're just listening, stop here */
			if (listen && s->state == SSL3_ST_SW_SRVR_HELLO_A)
				{
				ret = 2;
				s->d1->listen = 0;
				/* Set expected sequence numbers
				 * to continue the handshake.
				 */
				s->d1->handshake_read_seq = 2;
				s->d1->handshake_write_seq = 1;
				s->d1->next_handshake_write_seq = 1;
				goto end;
				}
			
			break;
			
		case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_A:
		case DTLS1_ST_SW_HELLO_VERIFY_REQUEST_B:

			ret = dtls1_send_hello_verify_request(s);
			if ( ret <= 0) goto end;
			s->state=SSL3_ST_SW_FLUSH;
			s->s3->tmp.next_state=SSL3_ST_SR_CLNT_HELLO_A;

			/* HelloVerifyRequest resets Finished MAC */
			if (s->version != DTLS1_BAD_VER)
				ssl3_init_finished_mac(s);
			break;
			
#ifndef OPENSSL_NO_SCTP
		case DTLS1_SCTP_ST_SR_READ_SOCK:
			
			if (BIO_dgram_sctp_msg_waiting(SSL_get_rbio(s)))		
				{
				s->s3->in_read_app_data=2;
				s->rwstate=SSL_READING;
				BIO_clear_retry_flags(SSL_get_rbio(s));
				BIO_set_retry_read(SSL_get_rbio(s));
				ret = -1;
				goto end;
				}
			
			s->state=SSL3_ST_SR_FINISHED_A;
			break;
			
		case DTLS1_SCTP_ST_SW_WRITE_SOCK:
			ret = BIO_dgram_sctp_wait_for_dry(SSL_get_wbio(s));
			if (ret < 0) goto end;
			
			if (ret == 0)
				{
				if (s->d1->next_state != SSL_ST_OK)
					{
					s->s3->in_read_app_data=2;
					s->rwstate=SSL_READING;
					BIO_clear_retry_flags(SSL_get_rbio(s));
					BIO_set_retry_read(SSL_get_rbio(s));
					ret = -1;
					goto end;
					}
				}

			s->state=s->d1->next_state;
			break;
#endif

		case SSL3_ST_SW_SRVR_HELLO_A:
		case SSL3_ST_SW_SRVR_HELLO_B:
			s->renegotiate = 2;
			dtls1_start_timer(s);
			ret=dtls1_send_server_hello(s);
			if (ret <= 0) goto end;

			if (s->hit)
				{
#ifndef OPENSSL_NO_SCTP
				/* Add new shared key for SCTP-Auth,
				 * will be ignored if no SCTP used.
				 */
				snprintf((char*) labelbuffer, sizeof(DTLS1_SCTP_AUTH_LABEL),
				         DTLS1_SCTP_AUTH_LABEL);

				SSL_export_keying_material(s, sctpauthkey,
				                           sizeof(sctpauthkey), labelbuffer,
				                           sizeof(labelbuffer), NULL, 0, 0);
				
				BIO_ctrl(SSL_get_wbio(s), BIO_CTRL_DGRAM_SCTP_ADD_AUTH_KEY,
                         sizeof(sctpauthkey), sctpauthkey);
#endif
#ifndef OPENSSL_NO_TLSEXT
				if (s->tlsext_ticket_expected)
					s->state=SSL3_ST_SW_SESSION_TICKET_A;
				else
					s->state=SSL3_ST_SW_CHANGE_A;
#else
				s->state=SSL3_ST_SW_CHANGE_A;
#endif
				}
			else
				s->state=SSL3_ST_SW_CERT_A;
			s->init_num=0;
			break;

		case SSL3_ST_SW_CERT_A:
		case SSL3_ST_SW_CERT_B:
			/* Check if it is anon DH or normal PSK */
			if (!(s->s3->tmp.new_cipher->algorithm_auth & SSL_aNULL)
				&& !(s->s3->tmp.new_cipher->algorithm_mkey & SSL_kPSK))
				{
				dtls1_start_timer(s);
				ret=dtls1_send_server_certificate(s);
				if (ret <= 0) goto end;
#ifndef OPENSSL_NO_TLSEXT
				if (s->tlsext_status_expected)
					s->state=SSL3_ST_SW_CERT_STATUS_A;
				else
					s->state=SSL3_ST_SW_KEY_EXCH_A;
				}
			else
				{
				skip = 1;
				s->state=SSL3_ST_SW_KEY_EXCH_A;
				}
#else
				}
