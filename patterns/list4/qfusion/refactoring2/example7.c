#ifndef OPENSSL_NO_SCTP
if (!BIO_dgram_is_sctp(SSL_get_wbio(s)))
#endif
                    if (!ssl_init_wbio_buffer(s, 1)) {
                        ret = -1;
                        s->state = SSL_ST_ERR;
                        goto end;
                    }
