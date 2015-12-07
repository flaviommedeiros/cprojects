#ifndef OPENSSL_NO_PSK
if (alg_k & SSL_kPSK) {
        param_len = 2;
        if (param_len > n) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_LENGTH_TOO_SHORT);
            goto f_err;
        }
        n2s(p, i);

        /*
         * Store PSK identity hint for later use, hint is used in
         * ssl3_send_client_key_exchange.  Assume that the maximum length of
         * a PSK identity hint can be as long as the maximum length of a PSK
         * identity.
         */
        if (i > PSK_MAX_IDENTITY_LEN) {
            al = SSL_AD_HANDSHAKE_FAILURE;
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_DATA_LENGTH_TOO_LONG);
            goto f_err;
        }
        if (i > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE,
                   SSL_R_BAD_PSK_IDENTITY_HINT_LENGTH);
            goto f_err;
        }
        param_len += i;

        s->session->psk_identity_hint = BUF_strndup((char *)p, i);
        if (s->session->psk_identity_hint == NULL) {
            al = SSL_AD_HANDSHAKE_FAILURE;
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_MALLOC_FAILURE);
            goto f_err;
        }

        p += i;
        n -= param_len;
    } else
#endif                          /* !OPENSSL_NO_PSK */
#ifndef OPENSSL_NO_SRP
    if (alg_k & SSL_kSRP) {
        param_len = 2;
        if (param_len > n) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_LENGTH_TOO_SHORT);
            goto f_err;
        }
        n2s(p, i);

        if (i > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_BAD_SRP_N_LENGTH);
            goto f_err;
        }
        param_len += i;

        if (!(s->srp_ctx.N = BN_bin2bn(p, i, NULL))) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_BN_LIB);
            goto err;
        }
        p += i;

        if (2 > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_LENGTH_TOO_SHORT);
            goto f_err;
        }
        param_len += 2;

        n2s(p, i);

        if (i > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_BAD_SRP_G_LENGTH);
            goto f_err;
        }
        param_len += i;

        if (!(s->srp_ctx.g = BN_bin2bn(p, i, NULL))) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_BN_LIB);
            goto err;
        }
        p += i;

        if (1 > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_LENGTH_TOO_SHORT);
            goto f_err;
        }
        param_len += 1;

        i = (unsigned int)(p[0]);
        p++;

        if (i > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_BAD_SRP_S_LENGTH);
            goto f_err;
        }
        param_len += i;

        if (!(s->srp_ctx.s = BN_bin2bn(p, i, NULL))) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_BN_LIB);
            goto err;
        }
        p += i;

        if (2 > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_LENGTH_TOO_SHORT);
            goto f_err;
        }
        param_len += 2;

        n2s(p, i);

        if (i > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_BAD_SRP_B_LENGTH);
            goto f_err;
        }
        param_len += i;

        if (!(s->srp_ctx.B = BN_bin2bn(p, i, NULL))) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_BN_LIB);
            goto err;
        }
        p += i;
        n -= param_len;

        if (!srp_verify_server_param(s, &al)) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_BAD_SRP_PARAMETERS);
            goto f_err;
        }

/* We must check if there is a certificate */
# ifndef OPENSSL_NO_RSA
        if (alg_a & SSL_aRSA)
            pkey =
                X509_get_pubkey(s->session->
                                sess_cert->peer_pkeys[SSL_PKEY_RSA_ENC].x509);
# else
        if (0) ;
# endif
# ifndef OPENSSL_NO_DSA
        else if (alg_a & SSL_aDSS)
            pkey =
                X509_get_pubkey(s->session->
                                sess_cert->peer_pkeys[SSL_PKEY_DSA_SIGN].
                                x509);
# endif
    } else
#endif                          /* !OPENSSL_NO_SRP */
#ifndef OPENSSL_NO_RSA
    if (alg_k & SSL_kRSA) {
        /* Temporary RSA keys only allowed in export ciphersuites */
        if (!SSL_C_IS_EXPORT(s->s3->tmp.new_cipher)) {
            al = SSL_AD_UNEXPECTED_MESSAGE;
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_UNEXPECTED_MESSAGE);
            goto f_err;
        }
        if ((rsa = RSA_new()) == NULL) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_MALLOC_FAILURE);
            goto err;
        }

        param_len = 2;
        if (param_len > n) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_LENGTH_TOO_SHORT);
            goto f_err;
        }
        n2s(p, i);

        if (i > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_BAD_RSA_MODULUS_LENGTH);
            goto f_err;
        }
        param_len += i;

        if (!(rsa->n = BN_bin2bn(p, i, rsa->n))) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_BN_LIB);
            goto err;
        }
        p += i;

        if (2 > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_LENGTH_TOO_SHORT);
            goto f_err;
        }
        param_len += 2;

        n2s(p, i);

        if (i > n - param_len) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_BAD_RSA_E_LENGTH);
            goto f_err;
        }
        param_len += i;

        if (!(rsa->e = BN_bin2bn(p, i, rsa->e))) {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_BN_LIB);
            goto err;
        }
        p += i;
        n -= param_len;

        /* this should be because we are using an export cipher */
        if (alg_a & SSL_aRSA)
            pkey =
                X509_get_pubkey(s->session->
                                sess_cert->peer_pkeys[SSL_PKEY_RSA_ENC].x509);
        else {
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, ERR_R_INTERNAL_ERROR);
            goto err;
        }

        if (EVP_PKEY_bits(pkey) <= SSL_C_EXPORT_PKEYLENGTH(s->s3->tmp.new_cipher)) {
            al = SSL_AD_UNEXPECTED_MESSAGE;
            SSLerr(SSL_F_SSL3_GET_KEY_EXCHANGE, SSL_R_UNEXPECTED_MESSAGE);
            goto f_err;
        }

        s->session->sess_cert->peer_rsa_tmp = rsa;
        rsa = NULL;
    }
