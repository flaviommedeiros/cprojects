switch (hashType) {
#ifndef NO_MD5
        case MD5:
            {
                Md5 md5;
                wc_InitMd5(&md5);
                wc_Md5Update(&md5, buffer, totalLen);
                wc_Md5Final(&md5, Ai);

                for (i = 1; i < iterations; i++) {
                    wc_Md5Update(&md5, Ai, u);
                    wc_Md5Final(&md5, Ai);
                }
            }
            break;
#endif /* NO_MD5 */
#ifndef NO_SHA
        case SHA:
            {
                Sha sha;
                ret = wc_InitSha(&sha);
                if (ret != 0)
                    break;
                wc_ShaUpdate(&sha, buffer, totalLen);
                wc_ShaFinal(&sha, Ai);

                for (i = 1; i < iterations; i++) {
                    wc_ShaUpdate(&sha, Ai, u);
                    wc_ShaFinal(&sha, Ai);
                }
            }
            break;
#endif /* NO_SHA */
#ifndef NO_SHA256
        case SHA256:
            {
                Sha256 sha256;
                ret = wc_InitSha256(&sha256);
                if (ret != 0)
                    break;

                ret = wc_Sha256Update(&sha256, buffer, totalLen);
                if (ret != 0)
                    break;

                ret = wc_Sha256Final(&sha256, Ai);
                if (ret != 0)
                    break;

                for (i = 1; i < iterations; i++) {
                    ret = wc_Sha256Update(&sha256, Ai, u);
                    if (ret != 0)
                        break;

                    ret = wc_Sha256Final(&sha256, Ai);
                    if (ret != 0)
                        break;
                }
            }
            break;
#endif /* NO_SHA256 */
#ifdef WOLFSSL_SHA512
        case SHA512:
            {
                Sha512 sha512;
                ret = wc_InitSha512(&sha512);
                if (ret != 0)
                    break;

                ret = wc_Sha512Update(&sha512, buffer, totalLen);
                if (ret != 0)
                    break;

                ret = wc_Sha512Final(&sha512, Ai);
                if (ret != 0)
                    break;

                for (i = 1; i < iterations; i++) {
                    ret = wc_Sha512Update(&sha512, Ai, u);
                    if (ret != 0)
                        break;

                    ret = wc_Sha512Final(&sha512, Ai);
                    if (ret != 0)
                        break;
                }
            }
            break;
#endif /* WOLFSSL_SHA512 */

        default:
            ret = BAD_FUNC_ARG;
            break;
    }
