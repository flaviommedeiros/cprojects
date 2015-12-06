switch (ssl->cipher)
    {
#ifndef CONFIG_SSL_SKELETON_MODE
        case SSL_AES128_SHA:
            {
                AES_CTX *aes_ctx = (AES_CTX *)malloc(sizeof(AES_CTX));
                AES_set_key(aes_ctx, key, iv, AES_MODE_128);

                if (is_decrypt)
                {
                    AES_convert_key(aes_ctx);
                }

                return (void *)aes_ctx;
            }

        case SSL_AES256_SHA:
            {
                AES_CTX *aes_ctx = (AES_CTX *)malloc(sizeof(AES_CTX));
                AES_set_key(aes_ctx, key, iv, AES_MODE_256);

                if (is_decrypt)
                {
                    AES_convert_key(aes_ctx);
                }

                return (void *)aes_ctx;
            }

        case SSL_RC4_128_MD5:
#endif
        case SSL_RC4_128_SHA:
            {
                RC4_CTX *rc4_ctx = (RC4_CTX *)malloc(sizeof(RC4_CTX));
                RC4_setup(rc4_ctx, key, 16);
                return (void *)rc4_ctx;
            }
    }
