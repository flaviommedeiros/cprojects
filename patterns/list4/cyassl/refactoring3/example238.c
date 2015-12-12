switch (algoOID) {
        #ifndef NO_RSA
            case RSAk:
                algoSz = sizeof(RSA_AlgoID);
                algoName = RSA_AlgoID;
                break;
        #endif /* NO_RSA */
        #ifdef HAVE_ECC 
            case ECDSAk:
                algoSz = sizeof(ECC_AlgoID);
                algoName = ECC_AlgoID;
                tagSz = 0;
                break;
        #endif /* HAVE_ECC */
        default:
            CYASSL_MSG("Unknown Key Algo");
            return 0;
        }
