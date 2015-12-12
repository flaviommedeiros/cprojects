#ifdef CYASSL_DTLS
if (DtlsPoolTimeout(ssl) == 0 && DtlsPoolSend(ssl) == 0)
                    goto retry;
                else
#endif
                    return -1;
