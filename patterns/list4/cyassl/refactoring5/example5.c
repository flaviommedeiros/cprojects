#ifdef HAVE_TLS_EXTENSIONS
if (TLSX_SupportExtensions(ssl)) {
                int ret = 0;
#else
            if (IsAtLeastTLSv1_2(ssl)) {
#endif
                /* Process the hello extension. Skip unsupported. */
                word16 totalExtSz;

                if ((i - begin) + OPAQUE16_LEN > helloSz)
                    return BUFFER_ERROR;

                ato16(&input[i], &totalExtSz);
                i += OPAQUE16_LEN;

                if ((i - begin) + totalExtSz > helloSz)
                    return BUFFER_ERROR;

#ifdef HAVE_TLS_EXTENSIONS
                if ((ret = TLSX_Parse(ssl, (byte *) input + i,
                                                     totalExtSz, 1, &clSuites)))
                    return ret;

                i += totalExtSz;
#else
                while (totalExtSz) {
                    word16 extId, extSz;

                    if (OPAQUE16_LEN + OPAQUE16_LEN > totalExtSz)
                        return BUFFER_ERROR;

                    ato16(&input[i], &extId);
                    i += OPAQUE16_LEN;
                    ato16(&input[i], &extSz);
                    i += OPAQUE16_LEN;

                    if (OPAQUE16_LEN + OPAQUE16_LEN + extSz > totalExtSz)
                        return BUFFER_ERROR;

                    if (extId == HELLO_EXT_SIG_ALGO) {
                        ato16(&input[i], &clSuites.hashSigAlgoSz);
                        i += OPAQUE16_LEN;

                        if (OPAQUE16_LEN + clSuites.hashSigAlgoSz > extSz)
                            return BUFFER_ERROR;

                        XMEMCPY(clSuites.hashSigAlgo, &input[i],
                            min(clSuites.hashSigAlgoSz, HELLO_EXT_SIGALGO_MAX));
                        i += clSuites.hashSigAlgoSz;

                        if (clSuites.hashSigAlgoSz > HELLO_EXT_SIGALGO_MAX)
                            clSuites.hashSigAlgoSz = HELLO_EXT_SIGALGO_MAX;
                    }
                    else
                        i += extSz;

                    totalExtSz -= OPAQUE16_LEN + OPAQUE16_LEN + extSz;
                }
#endif
                *inOutIdx = i;
            }
            else
                *inOutIdx = begin + helloSz; /* skip extensions */
        }
