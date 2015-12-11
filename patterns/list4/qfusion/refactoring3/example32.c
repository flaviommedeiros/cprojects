switch (s->state) {
        case SSL_ST_RENEGOTIATE:
            s->renegotiate = 1;
            s->state = SSL_ST_CONNECT;
            s->ctx->stats.sess_connect_renegotiate++;
            /* break */
        case SSL_ST_BEFORE:
        case SSL_ST_CONNECT:
        case SSL_ST_BEFORE | SSL_ST_CONNECT:
        case SSL_ST_OK | SSL_ST_CONNECT:

            s->server = 0;
            if (cb != NULL)
                cb(s, SSL_CB_HANDSHAKE_START, 1);

            if ((s->version & 0xff00) != (DTLS1_VERSION & 0xff00) &&
                (s->version & 0xff00) != (DTLS1_BAD_VER & 0xff00)) {
                SSLerr(SSL_F_DTLS1_CONNECT, ERR_R_INTERNAL_ERROR);
                ret = -1;
                s->state = SSL_ST_ERR;
                goto end;
            }

            /* s->version=SSL3_VERSION; */
            s->type = SSL_ST_CONNECT;

            if (s->init_buf == NULL) {
                if ((buf = BUF_MEM_new()) == NULL) {
                    ret = -1;
                    s->state = SSL_ST_ERR;
                    goto end;
                }
                if (!BUF_MEM_grow(buf, SSL3_RT_MAX_PLAIN_LENGTH)) {
                    ret = -1;
                    s->state = SSL_ST_ERR;
                    goto end;
                }
                s->init_buf = buf;
                buf = NULL;
            }

            if (!ssl3_setup_buffers(s)) {
                ret = -1;
                s->state = SSL_ST_ERR;
                goto end;
            }

            /* setup buffing BIO */
            if (!ssl_init_wbio_buffer(s, 0)) {
                ret = -1;
                s->state = SSL_ST_ERR;
                goto end;
            }

            /* don't push the buffering BIO quite yet */

            s->state = SSL3_ST_CW_CLNT_HELLO_A;
            s->ctx->stats.sess_connect++;
            s->init_num = 0;
            /* mark client_random uninitialized */
            memset(s->s3->client_random, 0, sizeof(s->s3->client_random));
            s->d1->send_cookie = 0;
            s->hit = 0;
            s->d1->change_cipher_spec_ok = 0;
            /*
             * Should have been reset by ssl3_get_finished, too.
             */
            s->s3->change_cipher_spec = 0;
            break;

#ifndef OPENSSL_NO_SCTP
        case DTLS1_SCTP_ST_CR_READ_SOCK:

            if (BIO_dgram_sctp_msg_waiting(SSL_get_rbio(s))) {
                s->s3->in_read_app_data = 2;
                s->rwstate = SSL_READING;
                BIO_clear_retry_flags(SSL_get_rbio(s));
                BIO_set_retry_read(SSL_get_rbio(s));
                ret = -1;
                goto end;
            }

            s->state = s->s3->tmp.next_state;
            break;

        case DTLS1_SCTP_ST_CW_WRITE_SOCK:
            /* read app data until dry event */

            ret = BIO_dgram_sctp_wait_for_dry(SSL_get_wbio(s));
            if (ret < 0)
                goto end;

            if (ret == 0) {
                s->s3->in_read_app_data = 2;
                s->rwstate = SSL_READING;
                BIO_clear_retry_flags(SSL_get_rbio(s));
                BIO_set_retry_read(SSL_get_rbio(s));
                ret = -1;
                goto end;
            }

            s->state = s->d1->next_state;
            break;
#endif

        case SSL3_ST_CW_CLNT_HELLO_A:
        case SSL3_ST_CW_CLNT_HELLO_B:

            s->shutdown = 0;

            /* every DTLS ClientHello resets Finished MAC */
            ssl3_init_finished_mac(s);

            dtls1_start_timer(s);
            ret = dtls1_client_hello(s);
            if (ret <= 0)
                goto end;

            if (s->d1->send_cookie) {
                s->state = SSL3_ST_CW_FLUSH;
                s->s3->tmp.next_state = SSL3_ST_CR_SRVR_HELLO_A;
            } else
                s->state = SSL3_ST_CR_SRVR_HELLO_A;

            s->init_num = 0;

#ifndef OPENSSL_NO_SCTP
            /* Disable buffering for SCTP */
            if (!BIO_dgram_is_sctp(SSL_get_wbio(s))) {
#endif
                /*
                 * turn on buffering for the next lot of output
                 */
                if (s->bbio != s->wbio)
                    s->wbio = BIO_push(s->bbio, s->wbio);
#ifndef OPENSSL_NO_SCTP
            }
#endif

            break;

        case SSL3_ST_CR_SRVR_HELLO_A:
        case SSL3_ST_CR_SRVR_HELLO_B:
            ret = ssl3_get_server_hello(s);
            if (ret <= 0)
                goto end;
            else {
                if (s->hit) {
#ifndef OPENSSL_NO_SCTP
                    /*
                     * Add new shared key for SCTP-Auth, will be ignored if
                     * no SCTP used.
                     */
                    snprintf((char *)labelbuffer,
                             sizeof(DTLS1_SCTP_AUTH_LABEL),
                             DTLS1_SCTP_AUTH_LABEL);

                    SSL_export_keying_material(s, sctpauthkey,
                                               sizeof(sctpauthkey),
                                               labelbuffer,
                                               sizeof(labelbuffer), NULL, 0,
                                               0);

                    BIO_ctrl(SSL_get_wbio(s),
                             BIO_CTRL_DGRAM_SCTP_ADD_AUTH_KEY,
                             sizeof(sctpauthkey), sctpauthkey);
#endif

                    s->state = SSL3_ST_CR_FINISHED_A;
                } else
                    s->state = DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A;
            }
            s->init_num = 0;
            break;

        case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_A:
        case DTLS1_ST_CR_HELLO_VERIFY_REQUEST_B:

            ret = dtls1_get_hello_verify(s);
            if (ret <= 0)
                goto end;
            dtls1_stop_timer(s);
            if (s->d1->send_cookie) /* start again, with a cookie */
                s->state = SSL3_ST_CW_CLNT_HELLO_A;
            else
                s->state = SSL3_ST_CR_CERT_A;
            s->init_num = 0;
            break;

        case SSL3_ST_CR_CERT_A:
        case SSL3_ST_CR_CERT_B:
            /* Check if it is anon DH or PSK */
            if (!(s->s3->tmp.new_cipher->algorithm_auth & SSL_aNULL) &&
                !(s->s3->tmp.new_cipher->algorithm_mkey & SSL_kPSK)) {
                ret = ssl3_get_server_certificate(s);
                if (ret <= 0)
                    goto end;
#ifndef OPENSSL_NO_TLSEXT
                if (s->tlsext_status_expected)
                    s->state = SSL3_ST_CR_CERT_STATUS_A;
                else
                    s->state = SSL3_ST_CR_KEY_EXCH_A;
            } else {
                skip = 1;
                s->state = SSL3_ST_CR_KEY_EXCH_A;
            }
#else
            }
