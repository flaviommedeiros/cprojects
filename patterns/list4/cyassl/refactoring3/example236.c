switch (algoOID) {
        #ifndef NO_RSA
            case CTC_MD5wRSA:
                algoSz = sizeof(md5wRSA_AlgoID);
                algoName = md5wRSA_AlgoID;
                break;

            case CTC_SHAwRSA:
                algoSz = sizeof(shawRSA_AlgoID);
                algoName = shawRSA_AlgoID;
                break;

            case CTC_SHA256wRSA:
                algoSz = sizeof(sha256wRSA_AlgoID);
                algoName = sha256wRSA_AlgoID;
                break;

            case CTC_SHA384wRSA:
                algoSz = sizeof(sha384wRSA_AlgoID);
                algoName = sha384wRSA_AlgoID;
                break;

            case CTC_SHA512wRSA:
                algoSz = sizeof(sha512wRSA_AlgoID);
                algoName = sha512wRSA_AlgoID;
                break;
        #endif /* NO_RSA */
        #ifdef HAVE_ECC 
            case CTC_SHAwECDSA:
                algoSz = sizeof(shawECDSA_AlgoID);
                algoName = shawECDSA_AlgoID;
                break;

            case CTC_SHA256wECDSA:
                algoSz = sizeof(sha256wECDSA_AlgoID);
                algoName = sha256wECDSA_AlgoID;
                break;

            case CTC_SHA384wECDSA:
                algoSz = sizeof(sha384wECDSA_AlgoID);
                algoName = sha384wECDSA_AlgoID;
                break;

            case CTC_SHA512wECDSA:
                algoSz = sizeof(sha512wECDSA_AlgoID);
                algoName = sha512wECDSA_AlgoID;
                break;
        #endif /* HAVE_ECC */
        default:
            CYASSL_MSG("Unknown Signature Algo");
            return 0;
        }
