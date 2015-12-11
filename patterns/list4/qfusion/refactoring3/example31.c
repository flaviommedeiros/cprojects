switch (EVP_MD_CTX_type(ctx)) {
    case NID_md5:
        MD5_Init((MD5_CTX *)md_state.c);
        md_final_raw = tls1_md5_final_raw;
        md_transform =
            (void (*)(void *ctx, const unsigned char *block))MD5_Transform;
        md_size = 16;
        sslv3_pad_length = 48;
        length_is_big_endian = 0;
        break;
    case NID_sha1:
        SHA1_Init((SHA_CTX *)md_state.c);
        md_final_raw = tls1_sha1_final_raw;
        md_transform =
            (void (*)(void *ctx, const unsigned char *block))SHA1_Transform;
        md_size = 20;
        break;
#ifndef OPENSSL_NO_SHA256
    case NID_sha224:
        SHA224_Init((SHA256_CTX *)md_state.c);
        md_final_raw = tls1_sha256_final_raw;
        md_transform =
            (void (*)(void *ctx, const unsigned char *block))SHA256_Transform;
        md_size = 224 / 8;
        break;
    case NID_sha256:
        SHA256_Init((SHA256_CTX *)md_state.c);
        md_final_raw = tls1_sha256_final_raw;
        md_transform =
            (void (*)(void *ctx, const unsigned char *block))SHA256_Transform;
        md_size = 32;
        break;
#endif
#ifndef OPENSSL_NO_SHA512
    case NID_sha384:
        SHA384_Init((SHA512_CTX *)md_state.c);
        md_final_raw = tls1_sha512_final_raw;
        md_transform =
            (void (*)(void *ctx, const unsigned char *block))SHA512_Transform;
        md_size = 384 / 8;
        md_block_size = 128;
        md_length_size = 16;
        break;
    case NID_sha512:
        SHA512_Init((SHA512_CTX *)md_state.c);
        md_final_raw = tls1_sha512_final_raw;
        md_transform =
            (void (*)(void *ctx, const unsigned char *block))SHA512_Transform;
        md_size = 64;
        md_block_size = 128;
        md_length_size = 16;
        break;
#endif
    default:
        /*
         * ssl3_cbc_record_digest_supported should have been called first to
         * check that the hash function is supported.
         */
        OPENSSL_assert(0);
        if (md_out_size)
            *md_out_size = -1;
        return;
    }
