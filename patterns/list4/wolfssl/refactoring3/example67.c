switch(ssl->specs.kea)
        {
    #ifndef NO_PSK
        case psk_kea:
        {
            byte    *output;
            word32   length, idx = RECORD_HEADER_SZ + HANDSHAKE_HEADER_SZ;
            int      sendSz;
            if (ssl->arrays->server_hint[0] == 0) return 0; /* don't send */

            /* include size part */
            length = (word32)XSTRLEN(ssl->arrays->server_hint);
            if (length > MAX_PSK_ID_LEN) {
                return SERVER_HINT_ERROR;
            }

            length += HINT_LEN_SZ;
            sendSz = length + HANDSHAKE_HEADER_SZ + RECORD_HEADER_SZ;

        #ifdef HAVE_QSH
            length += qshSz;
            sendSz += qshSz;
        #endif

        #ifdef WOLFSSL_DTLS
            if (ssl->options.dtls) {
                sendSz += DTLS_RECORD_EXTRA + DTLS_HANDSHAKE_EXTRA;
                idx    += DTLS_RECORD_EXTRA + DTLS_HANDSHAKE_EXTRA;
            }
        #endif
            /* check for available size */
            if ((ret = CheckAvailableSize(ssl, sendSz)) != 0) {
                return ret;
            }

            /* get ouput buffer */
            output = ssl->buffers.outputBuffer.buffer +
                     ssl->buffers.outputBuffer.length;

            AddHeaders(output, length, server_key_exchange, ssl);

            /* key data */
        #ifdef HAVE_QSH
            c16toa((word16)(length - qshSz - HINT_LEN_SZ), output + idx);
        #else
            c16toa((word16)(length - HINT_LEN_SZ), output + idx);
        #endif
            idx += HINT_LEN_SZ;
            XMEMCPY(output + idx, ssl->arrays->server_hint,length -HINT_LEN_SZ);

        #ifdef HAVE_QSH
            if (ssl->peerQSHKeyPresent) {
                if (qshSz > 0) {
                    idx = sendSz - qshSz;
                    if (QSH_KeyExchangeWrite(ssl, 1) != 0) {
                        return MEMORY_E;
                    }

                    /* extension type */
                    c16toa(TLSX_QUANTUM_SAFE_HYBRID, output + idx);
                    idx += OPAQUE16_LEN;

                    /* write to output and check amount written */
                    if (TLSX_QSHPK_Write(ssl->QSH_secret->list, output + idx)
                                                      > qshSz - OPAQUE16_LEN) {
                        return MEMORY_E;
                    }
                }
            }
        #endif

        #ifdef WOLFSSL_DTLS
            if (ssl->options.dtls) {
                if ((ret = DtlsPoolSave(ssl, output, sendSz)) != 0) {
                    return ret;
                }
            }
        #endif

            ret = HashOutput(ssl, output, sendSz, 0);
            if (ret != 0) {
                return ret;
            }

        #ifdef WOLFSSL_CALLBACKS
            if (ssl->hsInfoOn) {
                AddPacketName("ServerKeyExchange", &ssl->handShakeInfo);
            }
            if (ssl->toInfoOn) {
                AddPacketInfo("ServerKeyExchange", &ssl->timeoutInfo, output,
                                                            sendSz, ssl->heap);
            }
        #endif

            ssl->buffers.outputBuffer.length += sendSz;
            if (ssl->options.groupMessages) {
                ret = 0;
            }
            else {
                ret = SendBuffered(ssl);
            }
            ssl->options.serverState = SERVER_KEYEXCHANGE_COMPLETE;
            break;
        }
    #endif /*NO_PSK */

    #if !defined(NO_DH) && !defined(NO_PSK)
        case dhe_psk_kea:
        {
            byte    *output;
            word32   length, idx = RECORD_HEADER_SZ + HANDSHAKE_HEADER_SZ;
            word32   hintLen;
            int      sendSz;
            DhKey    dhKey;

            if (ssl->buffers.serverDH_P.buffer == NULL ||
            ssl->buffers.serverDH_G.buffer == NULL) {
                return NO_DH_PARAMS;
            }

            if (ssl->buffers.serverDH_Pub.buffer == NULL) {
                ssl->buffers.serverDH_Pub.buffer = (byte*)XMALLOC(
                        ssl->buffers.serverDH_P.length + 2, ssl->ctx->heap,
                        DYNAMIC_TYPE_DH);
                if (ssl->buffers.serverDH_Pub.buffer == NULL) {
                    return MEMORY_E;
                }
            }

            if (ssl->buffers.serverDH_Priv.buffer == NULL) {
                ssl->buffers.serverDH_Priv.buffer = (byte*)XMALLOC(
                        ssl->buffers.serverDH_P.length + 2, ssl->ctx->heap,
                        DYNAMIC_TYPE_DH);
                if (ssl->buffers.serverDH_Priv.buffer == NULL) {
                    return MEMORY_E;
                }
            }

            wc_InitDhKey(&dhKey);
            ret = wc_DhSetKey(&dhKey, ssl->buffers.serverDH_P.buffer,
                                   ssl->buffers.serverDH_P.length,
                                   ssl->buffers.serverDH_G.buffer,
                                   ssl->buffers.serverDH_G.length);
            if (ret == 0) {
                ret = wc_DhGenerateKeyPair(&dhKey, ssl->rng,
                                         ssl->buffers.serverDH_Priv.buffer,
                                        &ssl->buffers.serverDH_Priv.length,
                                         ssl->buffers.serverDH_Pub.buffer,
                                        &ssl->buffers.serverDH_Pub.length);
            }
            wc_FreeDhKey(&dhKey);
            if (ret != 0) {
                return ret;
            }

            length = LENGTH_SZ * 3 + /* p, g, pub */
                     ssl->buffers.serverDH_P.length +
                     ssl->buffers.serverDH_G.length +
                     ssl->buffers.serverDH_Pub.length;

            /* include size part */
            hintLen = (word32)XSTRLEN(ssl->arrays->server_hint);
            if (hintLen > MAX_PSK_ID_LEN) {
                return SERVER_HINT_ERROR;
            }
            length += hintLen + HINT_LEN_SZ;
            sendSz = length + HANDSHAKE_HEADER_SZ + RECORD_HEADER_SZ;

        #ifdef HAVE_QSH
            length += qshSz;
            sendSz += qshSz;
        #endif
        #ifdef WOLFSSL_DTLS
            if (ssl->options.dtls) {
                sendSz += DTLS_RECORD_EXTRA + DTLS_HANDSHAKE_EXTRA;
                idx    += DTLS_RECORD_EXTRA + DTLS_HANDSHAKE_EXTRA;
            }
        #endif

            /* check for available size */
            if ((ret = CheckAvailableSize(ssl, sendSz)) != 0) {
                return ret;
            }

            /* get ouput buffer */
            output = ssl->buffers.outputBuffer.buffer +
                     ssl->buffers.outputBuffer.length;

            AddHeaders(output, length, server_key_exchange, ssl);

            /* key data */
            c16toa((word16)hintLen, output + idx);
            idx += HINT_LEN_SZ;
            XMEMCPY(output + idx, ssl->arrays->server_hint, hintLen);
            idx += hintLen;

            /* add p, g, pub */
            c16toa((word16)ssl->buffers.serverDH_P.length, output + idx);
            idx += LENGTH_SZ;
            XMEMCPY(output + idx, ssl->buffers.serverDH_P.buffer,
                                  ssl->buffers.serverDH_P.length);
            idx += ssl->buffers.serverDH_P.length;

            /*  g */
            c16toa((word16)ssl->buffers.serverDH_G.length, output + idx);
            idx += LENGTH_SZ;
            XMEMCPY(output + idx, ssl->buffers.serverDH_G.buffer,
                                  ssl->buffers.serverDH_G.length);
            idx += ssl->buffers.serverDH_G.length;

            /*  pub */
            c16toa((word16)ssl->buffers.serverDH_Pub.length, output + idx);
            idx += LENGTH_SZ;
            XMEMCPY(output + idx, ssl->buffers.serverDH_Pub.buffer,
                                  ssl->buffers.serverDH_Pub.length);
            idx += ssl->buffers.serverDH_Pub.length;
            (void)idx; /* suppress analyzer warning, and keep idx current */

        #ifdef HAVE_QSH
            if (ssl->peerQSHKeyPresent) {
                if (qshSz > 0) {
                    idx = sendSz - qshSz;
                    QSH_KeyExchangeWrite(ssl, 1);

                    /* extension type */
                    c16toa(TLSX_QUANTUM_SAFE_HYBRID, output + idx);
                    idx += OPAQUE16_LEN;

                    /* write to output and check amount written */
                    if (TLSX_QSHPK_Write(ssl->QSH_secret->list, output + idx)
                                                      > qshSz - OPAQUE16_LEN) {
                        return MEMORY_E;
                    }
                }
            }
        #endif

        #ifdef WOLFSSL_DTLS
            if (ssl->options.dtls) {
                if ((ret = DtlsPoolSave(ssl, output, sendSz)) != 0) {
                    return ret;
                }
            }
        #endif

            ret = HashOutput(ssl, output, sendSz, 0);

            if (ret != 0) {
                return ret;
            }

        #ifdef WOLFSSL_CALLBACKS
            if (ssl->hsInfoOn) {
                AddPacketName("ServerKeyExchange", &ssl->handShakeInfo);
            }
            if (ssl->toInfoOn) {
                AddPacketInfo("ServerKeyExchange", &ssl->timeoutInfo, output,
                                                            sendSz, ssl->heap);
            }
        #endif

            ssl->buffers.outputBuffer.length += sendSz;
            if (ssl->options.groupMessages) {
                ret = 0;
            }
            else {
                ret = SendBuffered(ssl);
            }
            ssl->options.serverState = SERVER_KEYEXCHANGE_COMPLETE;
            break;
        }
    #endif /* !NO_DH && !NO_PSK */

    #ifdef HAVE_ECC
        case ecc_diffie_hellman_kea:
        {
            byte    *output;
            word32   length, idx = RECORD_HEADER_SZ + HANDSHAKE_HEADER_SZ;
            int      sendSz;
            word32   sigSz;
            word32   preSigSz, preSigIdx;
        #ifndef NO_RSA
            RsaKey   rsaKey;
        #endif
            ecc_key  dsaKey;
        #ifdef WOLFSSL_SMALL_STACK
            byte*    exportBuf = NULL;
        #else
            byte     exportBuf[MAX_EXPORT_ECC_SZ];
        #endif
            word32   expSz = MAX_EXPORT_ECC_SZ;

        #ifndef NO_OLD_TLS
            byte doMd5 = 0;
            byte doSha = 0;
        #endif
        #ifndef NO_SHA256
            byte doSha256 = 0;
        #endif
        #ifdef WOLFSSL_SHA384
            byte doSha384 = 0;
        #endif
        #ifdef WOLFSSL_SHA512
            byte doSha512 = 0;
        #endif

            if (ssl->specs.static_ecdh) {
                WOLFSSL_MSG("Using Static ECDH, not sending ServerKeyExchange");
                return 0;
            }

            /* curve type, named curve, length(1) */
            length = ENUM_LEN + CURVE_LEN + ENUM_LEN;
            /* pub key size */
            WOLFSSL_MSG("Using ephemeral ECDH");

            /* need ephemeral key now, create it if missing */
            if (ssl->eccTempKey == NULL) {
                /* alloc/init on demand */
                ssl->eccTempKey = (ecc_key*)XMALLOC(sizeof(ecc_key),
                                             ssl->ctx->heap, DYNAMIC_TYPE_ECC);
                if (ssl->eccTempKey == NULL) {
                    WOLFSSL_MSG("EccTempKey Memory error");
                    return MEMORY_E;
                }
                wc_ecc_init(ssl->eccTempKey);
            }
            if (ssl->eccTempKeyPresent == 0) {
                if (wc_ecc_make_key(ssl->rng, ssl->eccTempKeySz,
                                 ssl->eccTempKey) != 0) {
                    return ECC_MAKEKEY_ERROR;
                }
                ssl->eccTempKeyPresent = 1;
            }

        #ifdef WOLFSSL_SMALL_STACK
            exportBuf = (byte*)XMALLOC(MAX_EXPORT_ECC_SZ, NULL,
                                                      DYNAMIC_TYPE_TMP_BUFFER);
            if (exportBuf == NULL) {
                return MEMORY_E;
            }
        #endif

            if (wc_ecc_export_x963(ssl->eccTempKey, exportBuf, &expSz) != 0) {
                ERROR_OUT(ECC_EXPORT_ERROR, done_a);
            }
            length += expSz;

            preSigSz  = length;
            preSigIdx = idx;

        #ifndef NO_RSA
            ret = wc_InitRsaKey(&rsaKey, ssl->heap);
            if (ret != 0) {
                goto done_a;
            }
        #endif

            wc_ecc_init(&dsaKey);

            /* sig length */
            length += LENGTH_SZ;

            if (!ssl->buffers.key.buffer) {
            #ifndef NO_RSA
                wc_FreeRsaKey(&rsaKey);
            #endif
                wc_ecc_free(&dsaKey);
                ERROR_OUT(NO_PRIVATE_KEY, done_a);
            }

        #ifndef NO_RSA
            if (ssl->specs.sig_algo == rsa_sa_algo) {
                /* rsa sig size */
                word32 i = 0;
                ret = wc_RsaPrivateKeyDecode(ssl->buffers.key.buffer, &i,
                                          &rsaKey, ssl->buffers.key.length);
                if (ret != 0) {
                    goto done_a;
                }
                sigSz = wc_RsaEncryptSize(&rsaKey);
            } else
        #endif

            if (ssl->specs.sig_algo == ecc_dsa_sa_algo) {
                /* ecdsa sig size */
                word32 i = 0;
                ret = wc_EccPrivateKeyDecode(ssl->buffers.key.buffer, &i,
                                          &dsaKey, ssl->buffers.key.length);
                if (ret != 0) {
                    goto done_a;
                }
                sigSz = wc_ecc_sig_size(&dsaKey);  /* worst case estimate */
            }
            else {
            #ifndef NO_RSA
                wc_FreeRsaKey(&rsaKey);
            #endif
                wc_ecc_free(&dsaKey);
                ERROR_OUT(ALGO_ID_E, done_a);  /* unsupported type */
            }
            length += sigSz;

            if (IsAtLeastTLSv1_2(ssl)) {
                length += HASH_SIG_SIZE;
            }

            sendSz = length + HANDSHAKE_HEADER_SZ + RECORD_HEADER_SZ;

        #ifdef HAVE_QSH
            length += qshSz;
            sendSz += qshSz;
        #endif
        #ifdef WOLFSSL_DTLS
            if (ssl->options.dtls) {
                sendSz += DTLS_RECORD_EXTRA + DTLS_HANDSHAKE_EXTRA;
                idx    += DTLS_RECORD_EXTRA + DTLS_HANDSHAKE_EXTRA;
                preSigIdx = idx;
            }
        #endif
            /* check for available size */
            if ((ret = CheckAvailableSize(ssl, sendSz)) != 0) {
            #ifndef NO_RSA
                wc_FreeRsaKey(&rsaKey);
            #endif
                wc_ecc_free(&dsaKey);
                goto done_a;
            }

            /* get ouput buffer */
            output = ssl->buffers.outputBuffer.buffer +
                     ssl->buffers.outputBuffer.length;

            /* record and message headers will be added below, when we're sure
               of the sig length */

            /* key exchange data */
            output[idx++] = named_curve;
            output[idx++] = 0x00;          /* leading zero */
            output[idx++] = SetCurveId(wc_ecc_size(ssl->eccTempKey));
            output[idx++] = (byte)expSz;
            XMEMCPY(output + idx, exportBuf, expSz);
            idx += expSz;
            if (IsAtLeastTLSv1_2(ssl)) {
                byte setHash = 0;

                output[idx++] = ssl->suites->hashAlgo;
                output[idx++] = ssl->suites->sigAlgo;

                switch (ssl->suites->hashAlgo) {
                    case sha512_mac:
                        #ifdef WOLFSSL_SHA512
                            doSha512 = 1;
                            setHash  = 1;
                        #endif
                        break;

                    case sha384_mac:
                        #ifdef WOLFSSL_SHA384
                            doSha384 = 1;
                            setHash  = 1;
                        #endif
                        break;

                    case sha256_mac:
                        #ifndef NO_SHA256
                            doSha256 = 1;
                            setHash  = 1;
                        #endif
                        break;

                    case sha_mac:
                        #ifndef NO_OLD_TLS
                            doSha = 1;
                            setHash  = 1;
                        #endif
                        break;

                    default:
                        WOLFSSL_MSG("Bad hash sig algo");
                        break;
                }

                if (setHash == 0) {
                    #ifndef NO_RSA
                        wc_FreeRsaKey(&rsaKey);
                    #endif
                    wc_ecc_free(&dsaKey);
                    ERROR_OUT(ALGO_ID_E, done_a);
                }
            } else {
                /* only using sha and md5 for rsa */
                #ifndef NO_OLD_TLS
                    doSha = 1;
                    if (ssl->suites->sigAlgo == rsa_sa_algo) {
                        doMd5 = 1;
                    }
                #else
                    #ifndef NO_RSA
                        wc_FreeRsaKey(&rsaKey);
                    #endif
                    wc_ecc_free(&dsaKey);
                    ERROR_OUT(ALGO_ID_E, done_a);
                #endif
            }

            /* Signtaure length will be written later, when we're sure what it
               is */

        #ifdef HAVE_FUZZER
            if (ssl->fuzzerCb) {
                ssl->fuzzerCb(ssl, output + preSigIdx, preSigSz, 
                                               FUZZ_SIGNATURE, ssl->fuzzerCtx);
            }
        #endif

            /* do signature */
            {
        #ifndef NO_OLD_TLS
            #ifdef WOLFSSL_SMALL_STACK
                Md5*   md5  = NULL;
                Sha*   sha  = NULL;
            #else
                Md5    md5[1];
                Sha    sha[1];
            #endif
        #endif
            #ifdef WOLFSSL_SMALL_STACK
                byte*  hash = NULL;
            #else
                byte   hash[FINISHED_SZ];
            #endif
        #ifndef NO_SHA256
            #ifdef WOLFSSL_SMALL_STACK
                Sha256* sha256  = NULL;
                byte*   hash256 = NULL;
            #else
                Sha256  sha256[1];
                byte    hash256[SHA256_DIGEST_SIZE];
            #endif
        #endif
        #ifdef WOLFSSL_SHA384
            #ifdef WOLFSSL_SMALL_STACK
                Sha384* sha384  = NULL;
                byte*   hash384 = NULL;
            #else
                Sha384  sha384[1];
                byte    hash384[SHA384_DIGEST_SIZE];
            #endif
        #endif
        #ifdef WOLFSSL_SHA512
            #ifdef WOLFSSL_SMALL_STACK
                Sha512* sha512  = NULL;
                byte*   hash512 = NULL;
            #else
                Sha512  sha512[1];
                byte    hash512[SHA512_DIGEST_SIZE];
            #endif
        #endif

            #ifdef WOLFSSL_SMALL_STACK
                hash = (byte*)XMALLOC(FINISHED_SZ, NULL,
                                                      DYNAMIC_TYPE_TMP_BUFFER);
                if (hash == NULL) {
                    ERROR_OUT(MEMORY_E, done_a);
                }
            #endif

        #ifndef NO_OLD_TLS
                /* md5 */
            #ifdef WOLFSSL_SMALL_STACK
                if (doMd5) {
                    md5 = (Md5*)XMALLOC(sizeof(Md5), NULL,
                                        DYNAMIC_TYPE_TMP_BUFFER);
                    if (md5 == NULL) {
                        ERROR_OUT(MEMORY_E, done_a2);
                    }
                }
            #endif
                if (doMd5) {
                    wc_InitMd5(md5);
                    wc_Md5Update(md5, ssl->arrays->clientRandom, RAN_LEN);
                    wc_Md5Update(md5, ssl->arrays->serverRandom, RAN_LEN);
                    wc_Md5Update(md5, output + preSigIdx, preSigSz);
                    wc_Md5Final(md5, hash);
                }
                /* sha */
            #ifdef WOLFSSL_SMALL_STACK
                if (doSha) {
                    sha = (Sha*)XMALLOC(sizeof(Sha), NULL,
                                        DYNAMIC_TYPE_TMP_BUFFER);
                    if (sha == NULL) {
                        ERROR_OUT(MEMORY_E, done_a2);
                    }
                }
            #endif
                if (doSha) {
                    ret = wc_InitSha(sha);
                    if (ret != 0) {
                        goto done_a2;
                    }
                    wc_ShaUpdate(sha, ssl->arrays->clientRandom, RAN_LEN);
                    wc_ShaUpdate(sha, ssl->arrays->serverRandom, RAN_LEN);
                    wc_ShaUpdate(sha, output + preSigIdx, preSigSz);
                    wc_ShaFinal(sha, &hash[MD5_DIGEST_SIZE]);
                }
        #endif

        #ifndef NO_SHA256
            #ifdef WOLFSSL_SMALL_STACK
                if (doSha256) {
                    sha256 = (Sha256*)XMALLOC(sizeof(Sha256), NULL,
                                              DYNAMIC_TYPE_TMP_BUFFER);
                    hash256 = (byte*)XMALLOC(SHA256_DIGEST_SIZE, NULL,
                                             DYNAMIC_TYPE_TMP_BUFFER);
                    if (sha256 == NULL || hash256 == NULL) {
                        ERROR_OUT(MEMORY_E, done_a2);
                    }
                }
            #endif

                if (doSha256) {
                    if (!(ret = wc_InitSha256(sha256))
                    &&  !(ret = wc_Sha256Update(sha256,
                                           ssl->arrays->clientRandom, RAN_LEN))
                    &&  !(ret = wc_Sha256Update(sha256,
                                           ssl->arrays->serverRandom, RAN_LEN))
                    &&  !(ret = wc_Sha256Update(sha256,
                                           output + preSigIdx, preSigSz))) {
                        ret = wc_Sha256Final(sha256, hash256);
                    }
                    if (ret != 0) {
                        goto done_a2;
                    }
                }
        #endif

        #ifdef WOLFSSL_SHA384
            #ifdef WOLFSSL_SMALL_STACK
                if (doSha384) {
                    sha384 = (Sha384*)XMALLOC(sizeof(Sha384), NULL,
                                              DYNAMIC_TYPE_TMP_BUFFER);
                    hash384 = (byte*)XMALLOC(SHA384_DIGEST_SIZE, NULL,
                                             DYNAMIC_TYPE_TMP_BUFFER);
                    if (sha384 == NULL || hash384 == NULL) {
                        ERROR_OUT(MEMORY_E, done_a2);
                    }
                }
            #endif

                if (doSha384) {
                    if (!(ret = wc_InitSha384(sha384))
                    &&  !(ret = wc_Sha384Update(sha384,
                                           ssl->arrays->clientRandom, RAN_LEN))
                    &&  !(ret = wc_Sha384Update(sha384,
                                           ssl->arrays->serverRandom, RAN_LEN))
                    &&  !(ret = wc_Sha384Update(sha384,
                                           output + preSigIdx, preSigSz))) {
                        ret = wc_Sha384Final(sha384, hash384);
                    }
                    if (ret != 0) {
                        goto done_a2;
                    }
                }
        #endif

        #ifdef WOLFSSL_SHA512
            #ifdef WOLFSSL_SMALL_STACK
                if (doSha512) {
                    sha512 = (Sha512*)XMALLOC(sizeof(Sha512), NULL,
                                              DYNAMIC_TYPE_TMP_BUFFER);
                    hash512 = (byte*)XMALLOC(SHA512_DIGEST_SIZE, NULL,
                                             DYNAMIC_TYPE_TMP_BUFFER);
                    if (sha512 == NULL || hash512 == NULL) {
                        ERROR_OUT(MEMORY_E, done_a2);
                    }
                }
            #endif

                if (doSha512) {
                    if (!(ret = wc_InitSha512(sha512))
                    &&  !(ret = wc_Sha512Update(sha512,
                                           ssl->arrays->clientRandom, RAN_LEN))
                    &&  !(ret = wc_Sha512Update(sha512,
                                           ssl->arrays->serverRandom, RAN_LEN))
                    &&  !(ret = wc_Sha512Update(sha512,
                                           output + preSigIdx, preSigSz))) {
                        ret = wc_Sha512Final(sha512, hash512);
                    }
                    if (ret != 0) {
                        goto done_a2;
                    }
                }
        #endif

            #ifndef NO_RSA
                if (ssl->suites->sigAlgo == rsa_sa_algo) {
                    byte*  signBuffer = hash;
                    word32 signSz     = FINISHED_SZ;
                    byte   doUserRsa = 0;
                #ifdef WOLFSSL_SMALL_STACK
                    byte*  encodedSig = NULL;
                #else
                    byte   encodedSig[MAX_ENCODED_SIG_SZ];
                #endif

                #ifdef HAVE_PK_CALLBACKS
                    if (ssl->ctx->RsaSignCb)
                        doUserRsa = 1;
                #endif

                #ifdef WOLFSSL_SMALL_STACK
                    encodedSig = (byte*)XMALLOC(MAX_ENCODED_SIG_SZ, NULL,
                                                      DYNAMIC_TYPE_TMP_BUFFER);
                    if (encodedSig == NULL) {
                        ERROR_OUT(MEMORY_E, done_a2);
                    }
                #endif

                    if (IsAtLeastTLSv1_2(ssl)) {
                        byte* digest   = &hash[MD5_DIGEST_SIZE];
                        int   typeH    = SHAh;
                        int   digestSz = SHA_DIGEST_SIZE;

                        if (ssl->suites->hashAlgo == sha256_mac) {
                        #ifndef NO_SHA256
                            digest   = hash256;
                            typeH    = SHA256h;
                            digestSz = SHA256_DIGEST_SIZE;
                        #endif
                        }
                        else if (ssl->suites->hashAlgo == sha384_mac) {
                        #ifdef WOLFSSL_SHA384
                            digest   = hash384;
                            typeH    = SHA384h;
                            digestSz = SHA384_DIGEST_SIZE;
                        #endif
                        }
                        else if (ssl->suites->hashAlgo == sha512_mac) {
                        #ifdef WOLFSSL_SHA512
                            digest   = hash512;
                            typeH    = SHA512h;
                            digestSz = SHA512_DIGEST_SIZE;
                        #endif
                        }

                        if (digest == NULL) {
                            #ifndef NO_RSA
                                wc_FreeRsaKey(&rsaKey);
                            #endif
                            wc_ecc_free(&dsaKey);
                            ERROR_OUT(ALGO_ID_E, done_a2);
                        }
                        signSz = wc_EncodeSignature(encodedSig, digest,
                                                    digestSz, typeH);
                        signBuffer = encodedSig;
                    }
                    /* write sig size here */
                    c16toa((word16)sigSz, output + idx);
                    idx += LENGTH_SZ;

                    if (doUserRsa) {
                    #ifdef HAVE_PK_CALLBACKS
                        word32 ioLen = sigSz;
                        ret = ssl->ctx->RsaSignCb(ssl, signBuffer, signSz,
                                            output + idx, &ioLen,
                                            ssl->buffers.key.buffer,
                                            ssl->buffers.key.length,
                                            ssl->RsaSignCtx);
                    #endif /*HAVE_PK_CALLBACKS */
                    }
                    else {
                        ret = wc_RsaSSL_Sign(signBuffer, signSz, output + idx,
                                                     sigSz, &rsaKey, ssl->rng);
                    }

                    if (ret > 0) {
                        /* check for signature faults */
                        ret = VerifyRsaSign(output + idx, ret,
                                                  signBuffer, signSz, &rsaKey);
                    }
                    wc_FreeRsaKey(&rsaKey);
                    wc_ecc_free(&dsaKey);

                #ifdef WOLFSSL_SMALL_STACK
                    XFREE(encodedSig, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                #endif

                    if (ret < 0) {
                        goto done_a2;
                    }
                } else
            #endif

                if (ssl->suites->sigAlgo == ecc_dsa_sa_algo) {
                #ifndef NO_OLD_TLS
                    byte* digest = &hash[MD5_DIGEST_SIZE];
                    word32 digestSz = SHA_DIGEST_SIZE;
                #else
                    byte* digest = hash256;
                    word32 digestSz = SHA256_DIGEST_SIZE;
                #endif
                    word32 sz = sigSz;
                    byte   doUserEcc = 0;

                #if defined(HAVE_PK_CALLBACKS) && defined(HAVE_ECC)
                    if (ssl->ctx->EccSignCb) {
                        doUserEcc = 1;
                    }
                #endif

                    if (IsAtLeastTLSv1_2(ssl)) {
                        if (ssl->suites->hashAlgo == sha_mac) {
                        #ifndef NO_SHA
                            digest   = &hash[MD5_DIGEST_SIZE];
                            digestSz = SHA_DIGEST_SIZE;
                        #endif
                        }
                        else if (ssl->suites->hashAlgo == sha256_mac) {
                        #ifndef NO_SHA256
                            digest   = hash256;
                            digestSz = SHA256_DIGEST_SIZE;
                        #endif
                        }
                        else if (ssl->suites->hashAlgo == sha384_mac) {
                        #ifdef WOLFSSL_SHA384
                            digest   = hash384;
                            digestSz = SHA384_DIGEST_SIZE;
                        #endif
                        }
                        else if (ssl->suites->hashAlgo == sha512_mac) {
                        #ifdef WOLFSSL_SHA512
                            digest   = hash512;
                            digestSz = SHA512_DIGEST_SIZE;
                        #endif
                        }
                    }

                    if (doUserEcc) {
                    #if defined(HAVE_PK_CALLBACKS) && defined(HAVE_ECC)
                        ret = ssl->ctx->EccSignCb(ssl, digest, digestSz,
                                                  output + LENGTH_SZ + idx,
                                                  &sz,
                                                  ssl->buffers.key.buffer,
                                                  ssl->buffers.key.length,
                                                  ssl->EccSignCtx);
                    #endif
                    }
                    else {
                        ret = wc_ecc_sign_hash(digest, digestSz,
                             output + LENGTH_SZ + idx, &sz, ssl->rng, &dsaKey);
                    }
                #ifndef NO_RSA
                    wc_FreeRsaKey(&rsaKey);
                #endif
                    wc_ecc_free(&dsaKey);

                    if (ret < 0) {
                        goto done_a2;
                    }

                    /* Now that we know the real sig size, write it. */
                    c16toa((word16)sz, output + idx);

                    /* And adjust length and sendSz from estimates */
                    length += sz - sigSz;
                    sendSz += sz - sigSz;
                }

            done_a2:
        #ifdef WOLFSSL_SMALL_STACK
            #ifndef NO_OLD_TLS
                XFREE(md5,     NULL, DYNAMIC_TYPE_TMP_BUFFER);
                XFREE(sha,     NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
                XFREE(hash,    NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #ifndef NO_SHA256
                XFREE(sha256,  NULL, DYNAMIC_TYPE_TMP_BUFFER);
                XFREE(hash256, NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
            #ifdef WOLFSSL_SHA384
                XFREE(sha384,  NULL, DYNAMIC_TYPE_TMP_BUFFER);
                XFREE(hash384, NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
            #ifdef WOLFSSL_SHA512
                XFREE(sha512,  NULL, DYNAMIC_TYPE_TMP_BUFFER);
                XFREE(hash512, NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
        #endif

                if (ret < 0)
                    goto done_a;
            }

#ifdef HAVE_QSH
            if (ssl->peerQSHKeyPresent) {
                if (qshSz > 0) {
                    idx = sendSz - qshSz;
                    QSH_KeyExchangeWrite(ssl, 1);

                    /* extension type */
                    c16toa(TLSX_QUANTUM_SAFE_HYBRID, output + idx);
                    idx += OPAQUE16_LEN;

                    /* write to output and check amount written */
                    if (TLSX_QSHPK_Write(ssl->QSH_secret->list, output + idx)
                                                      > qshSz - OPAQUE16_LEN) {
                        return MEMORY_E;
                    }
                }
            }
#endif


            AddHeaders(output, length, server_key_exchange, ssl);

        #ifdef WOLFSSL_DTLS
            if (ssl->options.dtls) {
                if ((ret = DtlsPoolSave(ssl, output, sendSz)) != 0) {
                    goto done_a;
                }
            }
        #endif

            if ((ret = HashOutput(ssl, output, sendSz, 0)) != 0) {
                goto done_a;
            }

        #ifdef WOLFSSL_CALLBACKS
            if (ssl->hsInfoOn) {
                AddPacketName("ServerKeyExchange", &ssl->handShakeInfo);
            }
            if (ssl->toInfoOn) {
                AddPacketInfo("ServerKeyExchange", &ssl->timeoutInfo,
                              output, sendSz, ssl->heap);
            }
        #endif

            ssl->buffers.outputBuffer.length += sendSz;
            if (ssl->options.groupMessages) {
                ret = 0;
            }
            else {
                ret = SendBuffered(ssl);
            }
            ssl->options.serverState = SERVER_KEYEXCHANGE_COMPLETE;

        done_a:
        #ifdef WOLFSSL_SMALL_STACK
            XFREE(exportBuf, NULL, DYNAMIC_TYPE_TMP_BUFFER);
        #endif

            return ret;
        }
    #endif /* HAVE_ECC */

    #if !defined(NO_DH) && !defined(NO_RSA)
        case diffie_hellman_kea:
        {
            byte    *output;
            word32   length = 0, idx = RECORD_HEADER_SZ + HANDSHAKE_HEADER_SZ;
            int      sendSz;
            word32   sigSz = 0, i = 0;
            word32   preSigSz = 0, preSigIdx = 0;
            RsaKey   rsaKey;
            DhKey    dhKey;

            if (ssl->buffers.serverDH_P.buffer == NULL ||
            ssl->buffers.serverDH_G.buffer == NULL) {
                return NO_DH_PARAMS;
            }

            if (ssl->buffers.serverDH_Pub.buffer == NULL) {
                ssl->buffers.serverDH_Pub.buffer = (byte*)XMALLOC(
                        ssl->buffers.serverDH_P.length + 2, ssl->ctx->heap,
                        DYNAMIC_TYPE_DH);
                if (ssl->buffers.serverDH_Pub.buffer == NULL) {
                    return MEMORY_E;
                }
            }

            if (ssl->buffers.serverDH_Priv.buffer == NULL) {
                ssl->buffers.serverDH_Priv.buffer = (byte*)XMALLOC(
                        ssl->buffers.serverDH_P.length + 2, ssl->ctx->heap,
                        DYNAMIC_TYPE_DH);
                if (ssl->buffers.serverDH_Priv.buffer == NULL) {
                    return MEMORY_E;
                }
            }

            wc_InitDhKey(&dhKey);
            ret = wc_DhSetKey(&dhKey, ssl->buffers.serverDH_P.buffer,
                                   ssl->buffers.serverDH_P.length,
                                   ssl->buffers.serverDH_G.buffer,
                                   ssl->buffers.serverDH_G.length);
            if (ret == 0) {
                ret = wc_DhGenerateKeyPair(&dhKey, ssl->rng,
                                         ssl->buffers.serverDH_Priv.buffer,
                                        &ssl->buffers.serverDH_Priv.length,
                                         ssl->buffers.serverDH_Pub.buffer,
                                        &ssl->buffers.serverDH_Pub.length);
            }
            wc_FreeDhKey(&dhKey);

            if (ret != 0) {
                return ret;
            }

            length = LENGTH_SZ * 3;  /* p, g, pub */
            length += ssl->buffers.serverDH_P.length +
                      ssl->buffers.serverDH_G.length +
                      ssl->buffers.serverDH_Pub.length;

            preSigIdx = idx;
            preSigSz  = length;

            if (!ssl->options.usingAnon_cipher) {
                ret = wc_InitRsaKey(&rsaKey, ssl->heap);
                if (ret != 0) {
                    return ret;
                }

                /* sig length */
                length += LENGTH_SZ;

                if (!ssl->buffers.key.buffer) {
                    return NO_PRIVATE_KEY;
                }

                ret = wc_RsaPrivateKeyDecode(ssl->buffers.key.buffer, &i, 
                                             &rsaKey, ssl->buffers.key.length);
                if (ret == 0) {
                    sigSz = wc_RsaEncryptSize(&rsaKey);
                    length += sigSz;
                }
                else {
                    wc_FreeRsaKey(&rsaKey);
                    return ret;
                }

                if (IsAtLeastTLSv1_2(ssl)) {
                    length += HASH_SIG_SIZE;
                }
            }

            sendSz = length + HANDSHAKE_HEADER_SZ + RECORD_HEADER_SZ;

        #ifdef HAVE_QSH
            length += qshSz;
            sendSz += qshSz;
        #endif
        #ifdef WOLFSSL_DTLS
            if (ssl->options.dtls) {
                sendSz += DTLS_RECORD_EXTRA + DTLS_HANDSHAKE_EXTRA;
                idx    += DTLS_RECORD_EXTRA + DTLS_HANDSHAKE_EXTRA;
                preSigIdx = idx;
            }
        #endif

            /* check for available size */
            if ((ret = CheckAvailableSize(ssl, sendSz)) != 0) {
                if (!ssl->options.usingAnon_cipher) {
                    wc_FreeRsaKey(&rsaKey);
                }
                return ret;
            }

            /* get ouput buffer */
            output = ssl->buffers.outputBuffer.buffer +
                     ssl->buffers.outputBuffer.length;

            AddHeaders(output, length, server_key_exchange, ssl);

            /* add p, g, pub */
            c16toa((word16)ssl->buffers.serverDH_P.length, output + idx);
            idx += LENGTH_SZ;
            XMEMCPY(output + idx, ssl->buffers.serverDH_P.buffer,
                                  ssl->buffers.serverDH_P.length);
            idx += ssl->buffers.serverDH_P.length;

            /*  g */
            c16toa((word16)ssl->buffers.serverDH_G.length, output + idx);
            idx += LENGTH_SZ;
            XMEMCPY(output + idx, ssl->buffers.serverDH_G.buffer,
                                  ssl->buffers.serverDH_G.length);
            idx += ssl->buffers.serverDH_G.length;

            /*  pub */
            c16toa((word16)ssl->buffers.serverDH_Pub.length, output + idx);
            idx += LENGTH_SZ;
            XMEMCPY(output + idx, ssl->buffers.serverDH_Pub.buffer,
                                  ssl->buffers.serverDH_Pub.length);
            idx += ssl->buffers.serverDH_Pub.length;

        #ifdef HAVE_FUZZER
            if (ssl->fuzzerCb) {
                ssl->fuzzerCb(ssl, output + preSigIdx, preSigSz, 
                                               FUZZ_SIGNATURE, ssl->fuzzerCtx);
            }
        #endif

            /* Add signature */
            if (!ssl->options.usingAnon_cipher) {
        #ifndef NO_OLD_TLS
            #ifdef WOLFSSL_SMALL_STACK
                Md5*   md5  = NULL;
                Sha*   sha  = NULL;
            #else
                Md5    md5[1];
                Sha    sha[1];
            #endif
        #endif
            #ifdef WOLFSSL_SMALL_STACK
                byte*  hash = NULL;
            #else
                byte   hash[FINISHED_SZ];
            #endif
        #ifndef NO_SHA256
            #ifdef WOLFSSL_SMALL_STACK
                Sha256* sha256  = NULL;
                byte*   hash256 = NULL;
            #else
                Sha256  sha256[1];
                byte    hash256[SHA256_DIGEST_SIZE];
            #endif
        #endif
        #ifdef WOLFSSL_SHA384
            #ifdef WOLFSSL_SMALL_STACK
                Sha384* sha384  = NULL;
                byte*   hash384 = NULL;
            #else
                Sha384  sha384[1];
                byte    hash384[SHA384_DIGEST_SIZE];
            #endif
        #endif
        #ifdef WOLFSSL_SHA512
            #ifdef WOLFSSL_SMALL_STACK
                Sha512* sha512  = NULL;
                byte*   hash512 = NULL;
            #else
                Sha512  sha512[1];
                byte    hash512[SHA512_DIGEST_SIZE];
            #endif
        #endif

        #ifndef NO_OLD_TLS
            byte doMd5 = 0;
            byte doSha = 0;
        #endif
        #ifndef NO_SHA256
            byte doSha256 = 0;
        #endif
        #ifdef WOLFSSL_SHA384
            byte doSha384 = 0;
        #endif
        #ifdef WOLFSSL_SHA512
            byte doSha512 = 0;
        #endif

            /* Add hash/signature algo ID */
            if (IsAtLeastTLSv1_2(ssl)) {
                byte setHash = 0;

                output[idx++] = ssl->suites->hashAlgo;
                output[idx++] = ssl->suites->sigAlgo;

                switch (ssl->suites->hashAlgo) {
                    case sha512_mac:
                        #ifdef WOLFSSL_SHA512
                            doSha512 = 1;
                            setHash  = 1;
                        #endif
                        break;

                    case sha384_mac:
                        #ifdef WOLFSSL_SHA384
                            doSha384 = 1;
                            setHash  = 1;
                        #endif
                        break;

                    case sha256_mac:
                        #ifndef NO_SHA256
                            doSha256 = 1;
                            setHash  = 1;
                        #endif
                        break;

                    case sha_mac:
                        #ifndef NO_OLD_TLS
                            doSha = 1;
                            setHash  = 1;
                        #endif
                        break;

                    default:
                        WOLFSSL_MSG("Bad hash sig algo");
                        break;
                }

                if (setHash == 0) {
                    wc_FreeRsaKey(&rsaKey);
                    return ALGO_ID_E;
                }
            } else {
                /* only using sha and md5 for rsa */
                #ifndef NO_OLD_TLS
                    doSha = 1;
                    if (ssl->suites->sigAlgo == rsa_sa_algo) {
                        doMd5 = 1;
                    }
                #else
                    wc_FreeRsaKey(&rsaKey);
                    return ALGO_ID_E;
                #endif
            }

            /* signature size */
            c16toa((word16)sigSz, output + idx);
            idx += LENGTH_SZ;

            /* do signature */
            #ifdef WOLFSSL_SMALL_STACK
                hash = (byte*)XMALLOC(FINISHED_SZ, NULL,
                                                      DYNAMIC_TYPE_TMP_BUFFER);
                if (hash == NULL) {
                    return MEMORY_E; /* No heap commitment before this point,
                                        from now on, the resources are freed
                                        at done_b. */
                }
            #endif

        #ifndef NO_OLD_TLS
                /* md5 */
            #ifdef WOLFSSL_SMALL_STACK
                if (doMd5) {
                    md5 = (Md5*)XMALLOC(sizeof(Md5), NULL,
                                        DYNAMIC_TYPE_TMP_BUFFER);
                    if (md5 == NULL) {
                        ERROR_OUT(MEMORY_E, done_b);
                    }
                }
            #endif
                if (doMd5) {
                    wc_InitMd5(md5);
                    wc_Md5Update(md5, ssl->arrays->clientRandom, RAN_LEN);
                    wc_Md5Update(md5, ssl->arrays->serverRandom, RAN_LEN);
                    wc_Md5Update(md5, output + preSigIdx, preSigSz);
                    wc_Md5Final(md5, hash);
                }

                /* sha */
            #ifdef WOLFSSL_SMALL_STACK
                if (doSha) {
                    sha = (Sha*)XMALLOC(sizeof(Sha), NULL,
                                        DYNAMIC_TYPE_TMP_BUFFER);
                    if (sha == NULL) {
                        ERROR_OUT(MEMORY_E, done_b);
                    }
                }
            #endif

                if (doSha) {
                    if ((ret = wc_InitSha(sha)) != 0) {
                        goto done_b;
                    }
                    wc_ShaUpdate(sha, ssl->arrays->clientRandom, RAN_LEN);
                    wc_ShaUpdate(sha, ssl->arrays->serverRandom, RAN_LEN);
                    wc_ShaUpdate(sha, output + preSigIdx, preSigSz);
                    wc_ShaFinal(sha, &hash[MD5_DIGEST_SIZE]);
                }
        #endif

        #ifndef NO_SHA256
            #ifdef WOLFSSL_SMALL_STACK
                if (doSha256) {
                    sha256 = (Sha256*)XMALLOC(sizeof(Sha256), NULL,
                                              DYNAMIC_TYPE_TMP_BUFFER);
                    hash256 = (byte*)XMALLOC(SHA256_DIGEST_SIZE, NULL,
                                             DYNAMIC_TYPE_TMP_BUFFER);
                    if (sha256 == NULL || hash256 == NULL) {
                        ERROR_OUT(MEMORY_E, done_b);
                    }
                }
            #endif

                if (doSha256) {
                    if (!(ret = wc_InitSha256(sha256))
                    &&  !(ret = wc_Sha256Update(sha256,
                                           ssl->arrays->clientRandom, RAN_LEN))
                    &&  !(ret = wc_Sha256Update(sha256,
                                           ssl->arrays->serverRandom, RAN_LEN))
                    &&  !(ret = wc_Sha256Update(sha256,
                                           output + preSigIdx, preSigSz))) {
                        ret = wc_Sha256Final(sha256, hash256);
                    }
                    if (ret != 0) {
                        goto done_b;
                    }
                }
            #endif

        #ifdef WOLFSSL_SHA384
            #ifdef WOLFSSL_SMALL_STACK
                if (doSha384) {
                    sha384 = (Sha384*)XMALLOC(sizeof(Sha384), NULL,
                                              DYNAMIC_TYPE_TMP_BUFFER);
                    hash384 = (byte*)XMALLOC(SHA384_DIGEST_SIZE, NULL,
                                              DYNAMIC_TYPE_TMP_BUFFER);
                    if (sha384 == NULL || hash384 == NULL) {
                        ERROR_OUT(MEMORY_E, done_b);
                    }
                }
            #endif

                if (doSha384) {
                    if (!(ret = wc_InitSha384(sha384))
                    &&  !(ret = wc_Sha384Update(sha384,
                                           ssl->arrays->clientRandom, RAN_LEN))
                    &&  !(ret = wc_Sha384Update(sha384,
                                           ssl->arrays->serverRandom, RAN_LEN))
                    &&  !(ret = wc_Sha384Update(sha384,
                                           output + preSigIdx, preSigSz))) {
                        ret = wc_Sha384Final(sha384, hash384);
                    }
                    if (ret != 0) {
                        goto done_b;
                    }
                }
        #endif

        #ifdef WOLFSSL_SHA512
            #ifdef WOLFSSL_SMALL_STACK
                if (doSha512) {
                    sha512 = (Sha512*)XMALLOC(sizeof(Sha512), NULL,
                                              DYNAMIC_TYPE_TMP_BUFFER);
                    hash512 = (byte*)XMALLOC(SHA512_DIGEST_SIZE, NULL,
                                             DYNAMIC_TYPE_TMP_BUFFER);
                    if (sha512 == NULL || hash512 == NULL) {
                        ERROR_OUT(MEMORY_E, done_b);
                    }
                }
            #endif

                if (doSha512) {
                    if (!(ret = wc_InitSha512(sha512))
                    &&  !(ret = wc_Sha512Update(sha512,
                                           ssl->arrays->clientRandom, RAN_LEN))
                    &&  !(ret = wc_Sha512Update(sha512,
                                           ssl->arrays->serverRandom, RAN_LEN))
                    &&  !(ret = wc_Sha512Update(sha512,
                                           output + preSigIdx, preSigSz))) {
                        ret = wc_Sha512Final(sha512, hash512);
                    }
                    if (ret != 0) {
                        goto done_b;
                    }
                }
        #endif

            #ifndef NO_RSA
                if (ssl->suites->sigAlgo == rsa_sa_algo) {
                    byte*  signBuffer = hash;
                    word32 signSz     = FINISHED_SZ;
                #ifdef WOLFSSL_SMALL_STACK
                    byte*  encodedSig = NULL;
                #else
                    byte   encodedSig[MAX_ENCODED_SIG_SZ];
                #endif
                    byte   doUserRsa = 0;

                #ifdef HAVE_PK_CALLBACKS
                    if (ssl->ctx->RsaSignCb) {
                        doUserRsa = 1;
                    }
                #endif

                    if (IsAtLeastTLSv1_2(ssl)) {
                        byte* digest   = &hash[MD5_DIGEST_SIZE];
                        int   typeH    = SHAh;
                        int   digestSz = SHA_DIGEST_SIZE;
                        
                    #ifdef WOLFSSL_SMALL_STACK
                        encodedSig = (byte*)XMALLOC(MAX_ENCODED_SIG_SZ, NULL,
                                                      DYNAMIC_TYPE_TMP_BUFFER);
                        if (encodedSig == NULL)
                            ERROR_OUT(MEMORY_E, done_b);
                    #endif

                        if (ssl->suites->hashAlgo == sha256_mac) {
                        #ifndef NO_SHA256
                            digest   = hash256;
                            typeH    = SHA256h;
                            digestSz = SHA256_DIGEST_SIZE;
                        #endif
                        }
                        else if (ssl->suites->hashAlgo == sha384_mac) {
                        #ifdef WOLFSSL_SHA384
                            digest   = hash384;
                            typeH    = SHA384h;
                            digestSz = SHA384_DIGEST_SIZE;
                        #endif
                        }
                        else if (ssl->suites->hashAlgo == sha512_mac) {
                        #ifdef WOLFSSL_SHA512
                            digest   = hash512;
                            typeH    = SHA512h;
                            digestSz = SHA512_DIGEST_SIZE;
                        #endif
                        }

                        if (digest == NULL) {
                            ret = ALGO_ID_E;
                        } else {
                            signSz = wc_EncodeSignature(encodedSig, digest,
                                                        digestSz, typeH);
                            signBuffer = encodedSig;
                        }
                    }
                    if (doUserRsa && ret == 0) {
                    #ifdef HAVE_PK_CALLBACKS
                        word32 ioLen = sigSz;
                        ret = ssl->ctx->RsaSignCb(ssl, signBuffer, signSz,
                                                  output + idx, &ioLen,
                                                  ssl->buffers.key.buffer,
                                                  ssl->buffers.key.length,
                                                  ssl->RsaSignCtx);
                    #endif
                    } else if (ret == 0) {
                        ret = wc_RsaSSL_Sign(signBuffer, signSz, output + idx,
                                          sigSz, &rsaKey, ssl->rng);
                    }

                    if (ret > 0) {
                        /* check for signature faults */
                        ret = VerifyRsaSign(output + idx, ret,
                                            signBuffer, signSz, &rsaKey);
                    }

                    wc_FreeRsaKey(&rsaKey);

                #ifdef WOLFSSL_SMALL_STACK
                    XFREE(encodedSig, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                #endif
                }
            #endif

            done_b:
        #ifdef WOLFSSL_SMALL_STACK
            #ifndef NO_OLD_TLS
                XFREE(md5,     NULL, DYNAMIC_TYPE_TMP_BUFFER);
                XFREE(sha,     NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
                XFREE(hash,    NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #ifndef NO_SHA256
                XFREE(sha256,  NULL, DYNAMIC_TYPE_TMP_BUFFER);
                XFREE(hash256, NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
            #ifdef WOLFSSL_SHA384
                XFREE(sha384,  NULL, DYNAMIC_TYPE_TMP_BUFFER);
                XFREE(hash384, NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
            #ifdef WOLFSSL_SHA512
                XFREE(sha512,  NULL, DYNAMIC_TYPE_TMP_BUFFER);
                XFREE(hash512, NULL, DYNAMIC_TYPE_TMP_BUFFER);
            #endif
        #endif

                if (ret < 0) {
                    return ret;
                }
            }

    #ifdef HAVE_QSH
            if (ssl->peerQSHKeyPresent) {
                if (qshSz > 0) {
                    idx = sendSz - qshSz;
                    QSH_KeyExchangeWrite(ssl, 1);

                    /* extension type */
                    c16toa(TLSX_QUANTUM_SAFE_HYBRID, output + idx);
                    idx += OPAQUE16_LEN;

                    /* write to output and check amount written */
                    if (TLSX_QSHPK_Write(ssl->QSH_secret->list, output + idx)
                                                      > qshSz - OPAQUE16_LEN) {
                        return MEMORY_E;
                    }
                }
            }
    #endif

        #ifdef WOLFSSL_DTLS
            if (ssl->options.dtls) {
                if ((ret = DtlsPoolSave(ssl, output, sendSz)) != 0) {
                    return ret;
                }
            }
        #endif

            if ((ret = HashOutput(ssl, output, sendSz, 0)) != 0) {
                return ret;
            }

        #ifdef WOLFSSL_CALLBACKS
            if (ssl->hsInfoOn) {
                AddPacketName("ServerKeyExchange", &ssl->handShakeInfo);
            }
            if (ssl->toInfoOn) {
                AddPacketInfo("ServerKeyExchange", &ssl->timeoutInfo,
                              output, sendSz, ssl->heap);
            }
        #endif

            ssl->buffers.outputBuffer.length += sendSz;
            if (ssl->options.groupMessages) {
                ret = 0;
            }
            else {
                ret = SendBuffered(ssl);
            }
            ssl->options.serverState = SERVER_KEYEXCHANGE_COMPLETE;
            break;
        }
    #endif /* NO_DH */
        default:
            break;
        }
