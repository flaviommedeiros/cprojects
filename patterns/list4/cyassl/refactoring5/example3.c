#ifdef HAVE_TLS_EXTENSIONS
if (TLSX_SupportExtensions(ssl)) {
                int    ret = 0;
                word16 totalExtSz;

                if ((i - begin) + OPAQUE16_LEN > helloSz)
                    return BUFFER_ERROR;

                ato16(&input[i], &totalExtSz);
                i += OPAQUE16_LEN;

                if ((i - begin) + totalExtSz > helloSz)
                    return BUFFER_ERROR;

                if ((ret = TLSX_Parse(ssl, (byte *) input + i,
                                                          totalExtSz, 0, NULL)))
                    return ret;

                i += totalExtSz;
                *inOutIdx = i;
            }
            else
#endif
                *inOutIdx = begin + helloSz;
