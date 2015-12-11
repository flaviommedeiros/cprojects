#ifndef OPENSSL_NO_PSK
if (psk_key != NULL)
# else
    if (psk_key != NULL || jpake_secret)
# endif
    {
        if (s_debug)
            BIO_printf(bio_s_out,
                       "PSK key given or JPAKE in use, setting server callback\n");
        SSL_CTX_set_psk_server_callback(ctx, psk_server_cb);
    }
