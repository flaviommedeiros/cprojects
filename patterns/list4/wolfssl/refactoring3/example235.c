switch (type) {
#ifdef HAVE_NTRU
        case WOLFSSL_NTRU_EESS439:
        case WOLFSSL_NTRU_EESS593:
        case WOLFSSL_NTRU_EESS743:
            ret = TLSX_CreateNtruKey(ssl, type);
            break;
#endif
        default:
            WOLFSSL_MSG("Unknown type for creating NTRU key");
            return -1;
    }
