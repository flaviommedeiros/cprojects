#ifndef OPENSSL_NO_HEARTBEATS
if (!SSL_in_init(s) && !s->tlsext_hb_pending)
#else
    /* done, no need to send a retransmit */
    if (!SSL_in_init(s))
#endif
    {
        BIO_set_flags(SSL_get_rbio(s), BIO_FLAGS_READ);
        return code;
    }
