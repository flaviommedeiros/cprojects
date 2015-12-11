switch (type) {
    case EVP_CTRL_INIT:
        data(c)->key_bits = EVP_CIPHER_CTX_key_length(c) * 8;
        return 1;

    case EVP_CTRL_GET_RC2_KEY_BITS:
        *(int *)ptr = data(c)->key_bits;
        return 1;

    case EVP_CTRL_SET_RC2_KEY_BITS:
        if (arg > 0) {
            data(c)->key_bits = arg;
            return 1;
        }
        return 0;
# ifdef PBE_PRF_TEST
    case EVP_CTRL_PBE_PRF_NID:
        *(int *)ptr = NID_hmacWithMD5;
        return 1;
# endif

    default:
        return -1;
    }
