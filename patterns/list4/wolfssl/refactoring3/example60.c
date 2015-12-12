switch(key->name) {
#ifdef HAVE_NTRU
            case WOLFSSL_NTRU_EESS439:
                isNtru   = 1;
                break;
            case WOLFSSL_NTRU_EESS593:
                isNtru   = 1;
                break;
            case WOLFSSL_NTRU_EESS743:
                isNtru   = 1;
                break;
#endif
        default:
            WOLFSSL_MSG("Unknown QSH encryption scheme size!");
            return 0;
    }
