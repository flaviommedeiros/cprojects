#ifndef OPENSSL_NO_DSA
if (strcmp(name, PEM_STRING_DSA) == 0) {
            d2i = (D2I_OF(void)) d2i_DSAPrivateKey;
            if (xi->x_pkey != NULL) {
                if (!sk_X509_INFO_push(ret, xi))
                    goto err;
                if ((xi = X509_INFO_new()) == NULL)
                    goto err;
                goto start;
            }

            xi->enc_data = NULL;
            xi->enc_len = 0;

            xi->x_pkey = X509_PKEY_new();
            ptype = EVP_PKEY_DSA;
            pp = &xi->x_pkey->dec_pkey;
            if ((int)strlen(header) > 10) /* assume encrypted */
                raw = 1;
        } else
#endif
#ifndef OPENSSL_NO_EC
        if (strcmp(name, PEM_STRING_ECPRIVATEKEY) == 0) {
            d2i = (D2I_OF(void)) d2i_ECPrivateKey;
            if (xi->x_pkey != NULL) {
                if (!sk_X509_INFO_push(ret, xi))
                    goto err;
                if ((xi = X509_INFO_new()) == NULL)
                    goto err;
                goto start;
            }

            xi->enc_data = NULL;
            xi->enc_len = 0;

            xi->x_pkey = X509_PKEY_new();
            ptype = EVP_PKEY_EC;
            pp = &xi->x_pkey->dec_pkey;
            if ((int)strlen(header) > 10) /* assume encrypted */
                raw = 1;
        } else
#endif
        {
            d2i = NULL;
            pp = NULL;
        }
