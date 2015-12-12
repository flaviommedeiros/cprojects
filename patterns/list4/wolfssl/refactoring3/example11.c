switch (dCert->keyOID) {
        #ifndef NO_RSA
            case RSAk:
                {
                    word32 idx = 0;
                    int    keyRet = 0;

                    if (ssl->peerRsaKey == NULL) {
                        ssl->peerRsaKey = (RsaKey*)XMALLOC(sizeof(RsaKey),
                                                   ssl->heap, DYNAMIC_TYPE_RSA);
                        if (ssl->peerRsaKey == NULL) {
                            WOLFSSL_MSG("PeerRsaKey Memory error");
                            keyRet = MEMORY_E;
                        } else {
                            keyRet = wc_InitRsaKey(ssl->peerRsaKey,
                                                   ssl->ctx->heap);
                        }
                    } else if (ssl->peerRsaKeyPresent) {
                        /* don't leak on reuse */
                        wc_FreeRsaKey(ssl->peerRsaKey);
                        ssl->peerRsaKeyPresent = 0;
                        keyRet = wc_InitRsaKey(ssl->peerRsaKey, ssl->heap);
                    }

                    if (keyRet != 0 || wc_RsaPublicKeyDecode(dCert->publicKey,
                               &idx, ssl->peerRsaKey, dCert->pubKeySize) != 0) {
                        ret = PEER_KEY_ERROR;
                    }
                    else {
                        ssl->peerRsaKeyPresent = 1;
                        #ifdef HAVE_PK_CALLBACKS
                            #ifndef NO_RSA
                                ssl->buffers.peerRsaKey.buffer =
                                       (byte*)XMALLOC(dCert->pubKeySize,
                                               ssl->heap, DYNAMIC_TYPE_RSA);
                                if (ssl->buffers.peerRsaKey.buffer == NULL)
                                    ret = MEMORY_ERROR;
                                else {
                                    XMEMCPY(ssl->buffers.peerRsaKey.buffer,
                                           dCert->publicKey, dCert->pubKeySize);
                                    ssl->buffers.peerRsaKey.length =
                                            dCert->pubKeySize;
                                }
                            #endif /* NO_RSA */
                        #endif /*HAVE_PK_CALLBACKS */
                    }
                }
                break;
        #endif /* NO_RSA */
        #ifdef HAVE_NTRU
            case NTRUk:
                {
                    if (dCert->pubKeySize > sizeof(ssl->peerNtruKey)) {
                        ret = PEER_KEY_ERROR;
                    }
                    else {
                        XMEMCPY(ssl->peerNtruKey, dCert->publicKey,
                                                             dCert->pubKeySize);
                        ssl->peerNtruKeyLen = (word16)dCert->pubKeySize;
                        ssl->peerNtruKeyPresent = 1;
                    }
                }
                break;
        #endif /* HAVE_NTRU */
        #ifdef HAVE_ECC
            case ECDSAk:
                {
                    if (ssl->peerEccDsaKey == NULL) {
                        /* alloc/init on demand */
                        ssl->peerEccDsaKey = (ecc_key*)XMALLOC(sizeof(ecc_key),
                                              ssl->ctx->heap, DYNAMIC_TYPE_ECC);
                        if (ssl->peerEccDsaKey == NULL) {
                            WOLFSSL_MSG("PeerEccDsaKey Memory error");
                            return MEMORY_E;
                        }
                        wc_ecc_init(ssl->peerEccDsaKey);
                    } else if (ssl->peerEccDsaKeyPresent) {
                        /* don't leak on reuse */
                        wc_ecc_free(ssl->peerEccDsaKey);
                        ssl->peerEccDsaKeyPresent = 0;
                        wc_ecc_init(ssl->peerEccDsaKey);
                    }
                    if (wc_ecc_import_x963(dCert->publicKey, dCert->pubKeySize,
                                        ssl->peerEccDsaKey) != 0) {
                        ret = PEER_KEY_ERROR;
                    }
                    else {
                        ssl->peerEccDsaKeyPresent = 1;
                        #ifdef HAVE_PK_CALLBACKS
                            #ifdef HAVE_ECC
                                ssl->buffers.peerEccDsaKey.buffer =
                                       (byte*)XMALLOC(dCert->pubKeySize,
                                               ssl->heap, DYNAMIC_TYPE_ECC);
                                if (ssl->buffers.peerEccDsaKey.buffer == NULL)
                                    ret = MEMORY_ERROR;
                                else {
                                    XMEMCPY(ssl->buffers.peerEccDsaKey.buffer,
                                           dCert->publicKey, dCert->pubKeySize);
                                    ssl->buffers.peerEccDsaKey.length =
                                            dCert->pubKeySize;
                                }
                            #endif /* HAVE_ECC */
                        #endif /*HAVE_PK_CALLBACKS */
                    }
                }
                break;
        #endif /* HAVE_ECC */
            default:
                break;
        }
