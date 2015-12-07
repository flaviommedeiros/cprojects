#ifndef OPENSSL_NO_PSK
if (psk_key != NULL)
# else
    if (psk_key != NULL || jpake_secret)
# endif
    {
        if (c_debug)
            BIO_printf(bio_c_out,
                       "PSK key given or JPAKE in use, setting client callback\n");
        SSL_CTX_set_psk_client_callback(ctx, psk_client_cb);
    }
