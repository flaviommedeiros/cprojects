# ifdef BSAES_CAPABLE
if (BSAES_CAPABLE)
                xctx->stream = enc ? bsaes_xts_encrypt : bsaes_xts_decrypt;
            else
# endif
# ifdef VPAES_CAPABLE
            if (VPAES_CAPABLE) {
                if (enc) {
                    vpaes_set_encrypt_key(key, ctx->key_len * 4,
                                          &xctx->ks1.ks);
                    xctx->xts.block1 = (block128_f) vpaes_encrypt;
                } else {
                    vpaes_set_decrypt_key(key, ctx->key_len * 4,
                                          &xctx->ks1.ks);
                    xctx->xts.block1 = (block128_f) vpaes_decrypt;
                }

                vpaes_set_encrypt_key(key + ctx->key_len / 2,
                                      ctx->key_len * 4, &xctx->ks2.ks);
                xctx->xts.block2 = (block128_f) vpaes_encrypt;

                xctx->xts.key1 = &xctx->ks1;
                break;
            } else
# endif
                (void)0;
