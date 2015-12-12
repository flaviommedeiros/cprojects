switch (key->name) {
    #ifdef HAVE_NTRU
        case WOLFSSL_NTRU_EESS439:
        case WOLFSSL_NTRU_EESS593:
        case WOLFSSL_NTRU_EESS743:
            ret = NtruSecretEncrypt(key, in, szIn, out, &size);
            break;
    #endif
        default:
            WOLFSSL_MSG("Unknown QSH encryption key!");
            return -1;
    }
