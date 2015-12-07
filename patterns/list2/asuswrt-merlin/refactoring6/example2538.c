if (s->s3->send_alert[0] == SSL3_AL_FATAL
#ifdef DTLS1_AD_MISSING_HANDSHAKE_MESSAGE
            || s->s3->send_alert[1] == DTLS1_AD_MISSING_HANDSHAKE_MESSAGE
#endif
            )
            (void)BIO_flush(s->wbio);
