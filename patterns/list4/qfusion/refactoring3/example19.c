switch (res->type) {
#  ifndef OPENSSL_NO_RSA
        case EVP_PKEY_RSA:
            {
                RSA *rsa = NULL;

                CRYPTO_w_lock(CRYPTO_LOCK_EVP_PKEY);
                rsa = res->pkey.rsa;
                res->pkey.rsa = RSA_new();
                res->pkey.rsa->n = rsa->n;
                res->pkey.rsa->e = rsa->e;
                rsa->n = NULL;
                rsa->e = NULL;
                CRYPTO_w_unlock(CRYPTO_LOCK_EVP_PKEY);
                RSA_free(rsa);
            }
            break;
#  endif
        default:
            HWCRHKerr(HWCRHK_F_HWCRHK_LOAD_PUBKEY,
                      HWCRHK_R_CTRL_COMMAND_NOT_IMPLEMENTED);
            goto err;
        }
