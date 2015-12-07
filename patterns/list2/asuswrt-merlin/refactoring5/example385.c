# ifdef HWAES_CAPABLE
if (HWAES_CAPABLE) {
                HWAES_set_encrypt_key(key, ctx->key_len * 8, &cctx->ks.ks);

                CRYPTO_ccm128_init(&cctx->ccm, cctx->M, cctx->L,
                                   &cctx->ks, (block128_f) HWAES_encrypt);
                cctx->str = NULL;
                cctx->key_set = 1;
                break;
            } else
# endif
# ifdef VPAES_CAPABLE
            if (VPAES_CAPABLE) {
                vpaes_set_encrypt_key(key, ctx->key_len * 8, &cctx->ks.ks);
                CRYPTO_ccm128_init(&cctx->ccm, cctx->M, cctx->L,
                                   &cctx->ks, (block128_f) vpaes_encrypt);
                cctx->str = NULL;
                cctx->key_set = 1;
                break;
            }
