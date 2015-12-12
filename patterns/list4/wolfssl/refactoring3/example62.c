switch (ssl->specs.kea) {
        #ifndef NO_RSA
            case rsa_kea:
                ret = wc_RNG_GenerateBlock(ssl->rng, ssl->arrays->preMasterSecret,
                                                                    SECRET_LEN);
                if (ret != 0) {
                #ifdef WOLFSSL_SMALL_STACK
                    XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                #endif
                    return ret;
                }

                ssl->arrays->preMasterSecret[0] = ssl->chVersion.major;
                ssl->arrays->preMasterSecret[1] = ssl->chVersion.minor;
                ssl->arrays->preMasterSz = SECRET_LEN;

                if (ssl->peerRsaKey == NULL || ssl->peerRsaKeyPresent == 0) {
                #ifdef WOLFSSL_SMALL_STACK
                    XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                #endif
                    return NO_PEER_KEY;
                }

                if (doUserRsa) {
                #ifdef HAVE_PK_CALLBACKS
                    #ifndef NO_RSA
                        encSz = MAX_ENCRYPT_SZ;
                        ret = ssl->ctx->RsaEncCb(ssl,
                                            ssl->arrays->preMasterSecret,
                                            SECRET_LEN,
                                            encSecret, &encSz,
                                            ssl->buffers.peerRsaKey.buffer,
                                            ssl->buffers.peerRsaKey.length,
                                            ssl->RsaEncCtx);
                    #endif /* NO_RSA */
                #endif /*HAVE_PK_CALLBACKS */
                }
                else {
                    ret = wc_RsaPublicEncrypt(ssl->arrays->preMasterSecret,
                                 SECRET_LEN, encSecret, MAX_ENCRYPT_SZ,
                                 ssl->peerRsaKey, ssl->rng);
                    if (ret > 0) {
                        encSz = ret;
                        ret = 0;   /* set success to 0 */
                    }
                }
                break;
        #endif
        #ifndef NO_DH
            case diffie_hellman_kea:
                {
                    buffer  serverP   = ssl->buffers.serverDH_P;
                    buffer  serverG   = ssl->buffers.serverDH_G;
                    buffer  serverPub = ssl->buffers.serverDH_Pub;
                #ifdef WOLFSSL_SMALL_STACK
                    byte*   priv = NULL;
                #else
                    byte    priv[ENCRYPT_LEN];
                #endif
                    word32  privSz = 0;
                    DhKey   key;

                    if (serverP.buffer == 0 || serverG.buffer == 0 ||
                                               serverPub.buffer == 0) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return NO_PEER_KEY;
                    }

                #ifdef WOLFSSL_SMALL_STACK
                    priv = (byte*)XMALLOC(ENCRYPT_LEN, NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
                    if (priv == NULL) {
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                        return MEMORY_E;
                    }
                #endif

                    wc_InitDhKey(&key);
                    ret = wc_DhSetKey(&key, serverP.buffer, serverP.length,
                                   serverG.buffer, serverG.length);
                    if (ret == 0)
                        /* for DH, encSecret is Yc, agree is pre-master */
                        ret = wc_DhGenerateKeyPair(&key, ssl->rng, priv, &privSz,
                                                encSecret, &encSz);
                    if (ret == 0)
                        ret = wc_DhAgree(&key, ssl->arrays->preMasterSecret,
                                      &ssl->arrays->preMasterSz, priv, privSz,
                                      serverPub.buffer, serverPub.length);
                #ifdef WOLFSSL_SMALL_STACK
                    XFREE(priv, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                #endif
                    wc_FreeDhKey(&key);
                }
                break;
        #endif /* NO_DH */
        #ifndef NO_PSK
            case psk_kea:
                {
                    byte* pms = ssl->arrays->preMasterSecret;

                    ssl->arrays->psk_keySz = ssl->options.client_psk_cb(ssl,
                        ssl->arrays->server_hint, ssl->arrays->client_identity,
                        MAX_PSK_ID_LEN, ssl->arrays->psk_key, MAX_PSK_KEY_LEN);
                    if (ssl->arrays->psk_keySz == 0 ||
                        ssl->arrays->psk_keySz > MAX_PSK_KEY_LEN) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return PSK_KEY_ERROR;
                    }
                    encSz = (word32)XSTRLEN(ssl->arrays->client_identity);
                    if (encSz > MAX_PSK_ID_LEN) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return CLIENT_ID_ERROR;
                    }
                    XMEMCPY(encSecret, ssl->arrays->client_identity, encSz);

                    /* make psk pre master secret */
                    /* length of key + length 0s + length of key + key */
                    c16toa((word16)ssl->arrays->psk_keySz, pms);
                    pms += 2;
                    XMEMSET(pms, 0, ssl->arrays->psk_keySz);
                    pms += ssl->arrays->psk_keySz;
                    c16toa((word16)ssl->arrays->psk_keySz, pms);
                    pms += 2;
                    XMEMCPY(pms, ssl->arrays->psk_key, ssl->arrays->psk_keySz);
                    ssl->arrays->preMasterSz = ssl->arrays->psk_keySz * 2 + 4;
                    ForceZero(ssl->arrays->psk_key, ssl->arrays->psk_keySz);
                    ssl->arrays->psk_keySz = 0; /* No further need */
                }
                break;
        #endif /* NO_PSK */
        #if !defined(NO_DH) && !defined(NO_PSK)
            case dhe_psk_kea:
                {
                    byte* pms = ssl->arrays->preMasterSecret;
                    byte* es  = encSecret;
                    buffer  serverP   = ssl->buffers.serverDH_P;
                    buffer  serverG   = ssl->buffers.serverDH_G;
                    buffer  serverPub = ssl->buffers.serverDH_Pub;
                #ifdef WOLFSSL_SMALL_STACK
                    byte*   priv = NULL;
                #else
                    byte    priv[ENCRYPT_LEN];
                #endif
                    word32  privSz = 0;
                    word32  pubSz = 0;
                    word32  esSz = 0;
                    DhKey   key;

                    if (serverP.buffer == 0 || serverG.buffer == 0 ||
                                               serverPub.buffer == 0) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return NO_PEER_KEY;
                    }

                    ssl->arrays->psk_keySz = ssl->options.client_psk_cb(ssl,
                         ssl->arrays->server_hint, ssl->arrays->client_identity,
                         MAX_PSK_ID_LEN, ssl->arrays->psk_key, MAX_PSK_KEY_LEN);
                    if (ssl->arrays->psk_keySz == 0 ||
                                     ssl->arrays->psk_keySz > MAX_PSK_KEY_LEN) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return PSK_KEY_ERROR;
                    }
                    esSz = (word32)XSTRLEN(ssl->arrays->client_identity);

                    if (esSz > MAX_PSK_ID_LEN) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return CLIENT_ID_ERROR;
                    }

                #ifdef WOLFSSL_SMALL_STACK
                    priv = (byte*)XMALLOC(ENCRYPT_LEN, NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
                    if (priv == NULL) {
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                        return MEMORY_E;
                    }
                #endif
                    c16toa((word16)esSz, es);
                    es += OPAQUE16_LEN;
                    XMEMCPY(es, ssl->arrays->client_identity, esSz);
                    es += esSz;
                    encSz = esSz + OPAQUE16_LEN;

                    wc_InitDhKey(&key);
                    ret = wc_DhSetKey(&key, serverP.buffer, serverP.length,
                                   serverG.buffer, serverG.length);
                    if (ret == 0)
                        /* for DH, encSecret is Yc, agree is pre-master */
                        ret = wc_DhGenerateKeyPair(&key, ssl->rng, priv, &privSz,
                                                es + OPAQUE16_LEN, &pubSz);
                    if (ret == 0)
                        ret = wc_DhAgree(&key, pms + OPAQUE16_LEN,
                                      &ssl->arrays->preMasterSz, priv, privSz,
                                      serverPub.buffer, serverPub.length);
                    wc_FreeDhKey(&key);
                #ifdef WOLFSSL_SMALL_STACK
                    XFREE(priv, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                #endif
                    if (ret != 0) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return ret;
                    }

                    c16toa((word16)pubSz, es);
                    encSz += pubSz + OPAQUE16_LEN;
                    c16toa((word16)ssl->arrays->preMasterSz, pms);
                    ssl->arrays->preMasterSz += OPAQUE16_LEN;
                    pms += ssl->arrays->preMasterSz;

                    /* make psk pre master secret */
                    /* length of key + length 0s + length of key + key */
                    c16toa((word16)ssl->arrays->psk_keySz, pms);
                    pms += OPAQUE16_LEN;
                    XMEMCPY(pms, ssl->arrays->psk_key, ssl->arrays->psk_keySz);
                    ssl->arrays->preMasterSz +=
                                          ssl->arrays->psk_keySz + OPAQUE16_LEN;
                    ForceZero(ssl->arrays->psk_key, ssl->arrays->psk_keySz);
                    ssl->arrays->psk_keySz = 0; /* No further need */
                }
                break;
        #endif /* !NO_DH && !NO_PSK */
        #ifdef HAVE_NTRU
            case ntru_kea:
                {
                    word32 rc;
                    word16 cipherLen = MAX_ENCRYPT_SZ;
                    DRBG_HANDLE drbg;

                    ret = wc_RNG_GenerateBlock(ssl->rng,
                                      ssl->arrays->preMasterSecret, SECRET_LEN);
                    if (ret != 0) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return ret;
                    }

                    ssl->arrays->preMasterSz = SECRET_LEN;

                    if (ssl->peerNtruKeyPresent == 0) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return NO_PEER_KEY;
                    }

                    rc = ntru_crypto_drbg_external_instantiate(GetEntropy, &drbg);
                    if (rc != DRBG_OK) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return NTRU_DRBG_ERROR;
                    }

                    rc = ntru_crypto_ntru_encrypt(drbg, ssl->peerNtruKeyLen,
                                                  ssl->peerNtruKey,
                                                  ssl->arrays->preMasterSz,
                                                  ssl->arrays->preMasterSecret,
                                                  &cipherLen, encSecret);
                    ntru_crypto_drbg_uninstantiate(drbg);
                    if (rc != NTRU_OK) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return NTRU_ENCRYPT_ERROR;
                    }

                    encSz = cipherLen;
                    ret = 0;
                }
                break;
        #endif /* HAVE_NTRU */
        #ifdef HAVE_ECC
            case ecc_diffie_hellman_kea:
                {
                    ecc_key  myKey;
                    ecc_key* peerKey = NULL;
                    word32   size = MAX_ENCRYPT_SZ;

                    if (ssl->specs.static_ecdh) {
                        /* TODO: EccDsa is really fixed Ecc change naming */
                        if (!ssl->peerEccDsaKey || !ssl->peerEccDsaKeyPresent ||
                                                   !ssl->peerEccDsaKey->dp) {
                        #ifdef WOLFSSL_SMALL_STACK
                            XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                        #endif
                            return NO_PEER_KEY;
                        }
                        peerKey = ssl->peerEccDsaKey;
                    }
                    else {
                        if (!ssl->peerEccKey || !ssl->peerEccKeyPresent ||
                                                !ssl->peerEccKey->dp) {
                        #ifdef WOLFSSL_SMALL_STACK
                            XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                        #endif
                            return NO_PEER_KEY;
                        }
                        peerKey = ssl->peerEccKey;
                    }

                    if (peerKey == NULL) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return NO_PEER_KEY;
                    }

                    wc_ecc_init(&myKey);
                    ret = wc_ecc_make_key(ssl->rng, peerKey->dp->size, &myKey);
                    if (ret != 0) {
                    #ifdef WOLFSSL_SMALL_STACK
                        XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                    #endif
                        return ECC_MAKEKEY_ERROR;
                    }

                    /* precede export with 1 byte length */
                    ret = wc_ecc_export_x963(&myKey, encSecret + 1, &size);
                    encSecret[0] = (byte)size;
                    encSz = size + 1;

                    if (ret != 0)
                        ret = ECC_EXPORT_ERROR;
                    else {
                        size = sizeof(ssl->arrays->preMasterSecret);
                        ret  = wc_ecc_shared_secret(&myKey, peerKey,
                                                 ssl->arrays->preMasterSecret, &size);
                        if (ret != 0)
                            ret = ECC_SHARED_ERROR;
                    }

                    ssl->arrays->preMasterSz = size;
                    wc_ecc_free(&myKey);
                }
                break;
        #endif /* HAVE_ECC */
            default:
            #ifdef WOLFSSL_SMALL_STACK
                XFREE(encSecret, NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
                return ALGO_ID_E; /* unsupported kea */
        }
