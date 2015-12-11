#ifdef OPENSSL_IS_BORINGSSL
if (ERR_GET_LIB(n) == ERR_LIB_CIPHER
                && ERR_GET_REASON(n) == CIPHER_R_BAD_DECRYPT)
#else
            if (ERR_GET_LIB(n) == ERR_LIB_EVP
                && ERR_GET_REASON(n) == EVP_R_BAD_DECRYPT)
#endif
            {
                ERR_clear_error();
                SSL_CTX_set_default_passwd_cb_userdata(ssl->ctx, ++pwd);
                continue;
            }
