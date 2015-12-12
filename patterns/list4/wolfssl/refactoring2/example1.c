#ifdef WOLFSSL_SMALL_STACK
if (cert != NULL)
    #endif
        {
            InitDecodedCert(cert, der.buffer, der.length, NULL);
            if (ParseCertRelative(cert, CERT_TYPE, 0, NULL) == 0) {
                x509 = (WOLFSSL_X509*)XMALLOC(sizeof(WOLFSSL_X509), NULL,
                                                             DYNAMIC_TYPE_X509);
                if (x509 != NULL) {
                    InitX509(x509, 1);
                    if (CopyDecodedToX509(x509, cert) != 0) {
                        XFREE(x509, NULL, DYNAMIC_TYPE_X509);
                        x509 = NULL;
                    }
                }
            }

            FreeDecodedCert(cert);
        #ifdef WOLFSSL_SMALL_STACK
            XFREE(cert, NULL, DYNAMIC_TYPE_TMP_BUFFER);
        #endif
        }
