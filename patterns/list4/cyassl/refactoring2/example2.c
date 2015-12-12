#ifdef CYASSL_SMALL_STACK
if (cert != NULL)
    #endif
        {
            InitDecodedCert(cert, chain->certs[idx].buffer,
                                  chain->certs[idx].length, NULL);

            if ((ret = ParseCertRelative(cert, CERT_TYPE, 0, NULL)) != 0)
                CYASSL_MSG("Failed to parse cert");
            else {
                x509 = (CYASSL_X509*)XMALLOC(sizeof(CYASSL_X509), NULL,
                                                             DYNAMIC_TYPE_X509);
                if (x509 == NULL) {
                    CYASSL_MSG("Failed alloc X509");
                }
                else {
                    InitX509(x509, 1);

                    if ((ret = CopyDecodedToX509(x509, cert)) != 0) {
                        CYASSL_MSG("Failed to copy decoded");
                        XFREE(x509, NULL, DYNAMIC_TYPE_X509);
                        x509 = NULL;
                    }
                }
            }

            FreeDecodedCert(cert);
        #ifdef CYASSL_SMALL_STACK
            XFREE(cert, NULL, DYNAMIC_TYPE_TMP_BUFFER);
        #endif
        }
