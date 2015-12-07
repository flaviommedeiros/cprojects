#ifndef OPENSSL_NO_SCTP
if (BIO_dgram_is_sctp(SSL_get_wbio(s))) {
                s->d1->next_state = SSL3_ST_CW_CHANGE_A;
                s->state = DTLS1_SCTP_ST_CW_WRITE_SOCK;
            } else
#endif
                s->state = SSL3_ST_CW_CHANGE_A;
