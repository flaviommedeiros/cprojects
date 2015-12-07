# ifdef VPAES_CAPABLE
if (VPAES_CAPABLE) {
        ret = vpaes_set_encrypt_key(key, ctx->key_len * 8, &dat->ks.ks);
        dat->block = (block128_f) vpaes_encrypt;
        dat->stream.cbc = mode == EVP_CIPH_CBC_MODE ?
            (cbc128_f) vpaes_cbc_encrypt : NULL;
    } else
# endif
    {
        ret = AES_set_encrypt_key(key, ctx->key_len * 8, &dat->ks.ks);
        dat->block = (block128_f) AES_encrypt;
        dat->stream.cbc = mode == EVP_CIPH_CBC_MODE ?
            (cbc128_f) AES_cbc_encrypt : NULL;
# ifdef AES_CTR_ASM
        if (mode == EVP_CIPH_CTR_MODE)
            dat->stream.ctr = (ctr128_f) AES_ctr32_encrypt;
# endif
    }
