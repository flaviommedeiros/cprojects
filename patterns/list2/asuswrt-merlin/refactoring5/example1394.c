#ifndef OPENSSL_NO_SRP
if (srp_verifier_file != NULL) {
        srp_callback_parm.vb = SRP_VBASE_new(srpuserseed);
        srp_callback_parm.user = NULL;
        srp_callback_parm.login = NULL;
        if ((ret =
             SRP_VBASE_init(srp_callback_parm.vb,
                            srp_verifier_file)) != SRP_NO_ERROR) {
            BIO_printf(bio_err,
                       "Cannot initialize SRP verifier file \"%s\":ret=%d\n",
                       srp_verifier_file, ret);
            goto end;
        }
        SSL_CTX_set_verify(ctx, SSL_VERIFY_NONE, verify_callback);
        SSL_CTX_set_srp_cb_arg(ctx, &srp_callback_parm);
        SSL_CTX_set_srp_username_callback(ctx, ssl_srp_server_param_cb);
    } else
#endif
    if (CAfile != NULL) {
        SSL_CTX_set_client_CA_list(ctx, SSL_load_client_CA_file(CAfile));
#ifndef OPENSSL_NO_TLSEXT
        if (ctx2)
            SSL_CTX_set_client_CA_list(ctx2, SSL_load_client_CA_file(CAfile));
#endif
    }
