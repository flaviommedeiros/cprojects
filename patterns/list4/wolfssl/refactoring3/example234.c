switch(name) {
        #ifdef HAVE_NTRU
            case WOLFSSL_NTRU_EESS439:
            case WOLFSSL_NTRU_EESS593:
            case WOLFSSL_NTRU_EESS743:
                    return 1;
        #endif
            case WOLFSSL_LWE_XXX:
            case WOLFSSL_HFE_XXX:
                    return 0; /* not supported yet */

        default:
            return 0;
    }
