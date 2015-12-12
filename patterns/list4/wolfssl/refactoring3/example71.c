switch (ssl->specs.kea) {
        #ifndef NO_RSA
            case rsa_kea:
            {
                word32 idx = 0;
                RsaKey key;
                byte   doUserRsa = 0;

                #ifdef HAVE_PK_CALLBACKS
                    if (ssl->ctx->RsaDecCb) {
                        doUserRsa = 1;
                    }
                #endif

                ret = wc_InitRsaKey(&key, ssl->heap);
                if (ret != 0) {
                    return ret;
                }

                if (!ssl->buffers.key.buffer) {
                    return NO_PRIVATE_KEY;
                }
                
                ret = wc_RsaPrivateKeyDecode(ssl->buffers.key.buffer, &idx,
                                             &key, ssl->buffers.key.length);

                if (ret == 0) {
                    length = wc_RsaEncryptSize(&key);
                    ssl->arrays->preMasterSz = SECRET_LEN;

                    if (ssl->options.tls) {
                        word16 check;

                        if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                            return BUFFER_ERROR;
                        }

                        ato16(input + *inOutIdx, &check);
                        *inOutIdx += OPAQUE16_LEN;

                        if ((word32) check != length) {
                            WOLFSSL_MSG("RSA explicit size doesn't match");
                            wc_FreeRsaKey(&key);
                            return RSA_PRIVATE_ERROR;
                        }
                    }

                    if ((*inOutIdx - begin) + length > size) {
                        WOLFSSL_MSG("RSA message too big");
                        wc_FreeRsaKey(&key);
                        return BUFFER_ERROR;
                    }

                    if (doUserRsa) {
                        #ifdef HAVE_PK_CALLBACKS
                            ret = ssl->ctx->RsaDecCb(ssl,
                                        input + *inOutIdx, length, &out,
                                        ssl->buffers.key.buffer,
                                        ssl->buffers.key.length,
                                        ssl->RsaDecCtx);
                        #endif
                    }
                    else {
                        ret = wc_RsaPrivateDecryptInline(input + *inOutIdx, length,
                                                                    &out, &key);
                    }

                    *inOutIdx += length;

                    if (ret == SECRET_LEN) {
                        XMEMCPY(ssl->arrays->preMasterSecret, out, SECRET_LEN);
                        if (ssl->arrays->preMasterSecret[0] !=
                                                           ssl->chVersion.major
                            || ssl->arrays->preMasterSecret[1] !=
                                                           ssl->chVersion.minor) {
                            ret = PMS_VERSION_ERROR;
                        }
                        else
                        {
                #ifdef HAVE_QSH
                            if (ssl->options.haveQSH) {
                                /* extension name */
                                ato16(input + *inOutIdx, &name);
                                *inOutIdx += OPAQUE16_LEN;

                                if (name == TLSX_QUANTUM_SAFE_HYBRID) {
                                    /* if qshSz is larger than 0 it is the
                                       length of buffer used */
                                    if ((qshSz = TLSX_QSHCipher_Parse(ssl, input
                                                  + *inOutIdx, size - *inOutIdx
                                                  + begin, 1)) < 0) {
                                        return qshSz;
                                    }
                                    *inOutIdx += qshSz;
                                }
                                else {
                                    /* unknown extension sent client ignored
                                       handshake */
                                    return BUFFER_ERROR;
                                }
                            }
                #endif
                            ret = MakeMasterSecret(ssl);
                         }
                    }
                    else {
                        ret = RSA_PRIVATE_ERROR;
                    }
                }

                wc_FreeRsaKey(&key);
            }
            break;
        #endif
        #ifndef NO_PSK
            case psk_kea:
            {
                byte* pms = ssl->arrays->preMasterSecret;
                word16 ci_sz;

                if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                    return BUFFER_ERROR;
                }

                ato16(input + *inOutIdx, &ci_sz);
                *inOutIdx += OPAQUE16_LEN;

                if (ci_sz > MAX_PSK_ID_LEN) {
                    return CLIENT_ID_ERROR;
                }

                if ((*inOutIdx - begin) + ci_sz > size) {
                    return BUFFER_ERROR;
                }

                XMEMCPY(ssl->arrays->client_identity, input + *inOutIdx, ci_sz);
                *inOutIdx += ci_sz;

                ssl->arrays->client_identity[min(ci_sz, MAX_PSK_ID_LEN-1)] = 0;
                ssl->arrays->psk_keySz = ssl->options.server_psk_cb(ssl,
                    ssl->arrays->client_identity, ssl->arrays->psk_key,
                    MAX_PSK_KEY_LEN);

                if (ssl->arrays->psk_keySz == 0 ||
                                       ssl->arrays->psk_keySz > MAX_PSK_KEY_LEN) {
                    return PSK_KEY_ERROR;
                }

                /* make psk pre master secret */
                /* length of key + length 0s + length of key + key */
                c16toa((word16) ssl->arrays->psk_keySz, pms);
                pms += OPAQUE16_LEN;

                XMEMSET(pms, 0, ssl->arrays->psk_keySz);
                pms += ssl->arrays->psk_keySz;

                c16toa((word16) ssl->arrays->psk_keySz, pms);
                pms += OPAQUE16_LEN;

                XMEMCPY(pms, ssl->arrays->psk_key, ssl->arrays->psk_keySz);
                ssl->arrays->preMasterSz = ssl->arrays->psk_keySz * 2 + 4;

            #ifdef HAVE_QSH
                if (ssl->options.haveQSH) {
                    /* extension name */
                    ato16(input + *inOutIdx, &name);
                    *inOutIdx += OPAQUE16_LEN;

                    if (name == TLSX_QUANTUM_SAFE_HYBRID) {
                        /* if qshSz is larger than 0 it is the length of
                           buffer used */
                        if ((qshSz = TLSX_QSHCipher_Parse(ssl, input + *inOutIdx,
                                              size - *inOutIdx + begin, 1)) < 0) {
                            return qshSz;
                        }
                        *inOutIdx += qshSz;
                    }
                    else {
                        /* unknown extension sent client ignored
                           handshake */
                        return BUFFER_ERROR;
                    }
                }
            #endif
                ret = MakeMasterSecret(ssl);

                /* No further need for PSK */
                ForceZero(ssl->arrays->psk_key, ssl->arrays->psk_keySz);
                ssl->arrays->psk_keySz = 0;
            }
            break;
        #endif /* NO_PSK */
        #ifdef HAVE_NTRU
            case ntru_kea:
            {
                word16 cipherLen;
                word16 plainLen = sizeof(ssl->arrays->preMasterSecret);

                if (!ssl->buffers.key.buffer) {
                    return NO_PRIVATE_KEY;
                }

                if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                    return BUFFER_ERROR;
                }

                ato16(input + *inOutIdx, &cipherLen);
                *inOutIdx += OPAQUE16_LEN;

                if (cipherLen > MAX_NTRU_ENCRYPT_SZ) {
                    return NTRU_KEY_ERROR;
                }

                if ((*inOutIdx - begin) + cipherLen > size) {
                    return BUFFER_ERROR;
                }

                if (NTRU_OK != ntru_crypto_ntru_decrypt(
                            (word16) ssl->buffers.key.length,
                            ssl->buffers.key.buffer, cipherLen,
                            input + *inOutIdx, &plainLen,
                            ssl->arrays->preMasterSecret)) {
                    return NTRU_DECRYPT_ERROR;
                }

                if (plainLen != SECRET_LEN) {
                    return NTRU_DECRYPT_ERROR;
                }

                *inOutIdx += cipherLen;

            #ifdef HAVE_QSH
                if (ssl->options.haveQSH) {
                    /* extension name */
                    ato16(input + *inOutIdx, &name);
                    *inOutIdx += OPAQUE16_LEN;

                    if (name == TLSX_QUANTUM_SAFE_HYBRID) {
                        /* if qshSz is larger than 0 it is the length of
                           buffer used */
                        if ((qshSz = TLSX_QSHCipher_Parse(ssl, input + *inOutIdx,
                                              size - *inOutIdx + begin, 1)) < 0) {
                            return qshSz;
                        }
                        *inOutIdx += qshSz;
                    }
                    else {
                        /* unknown extension sent client ignored
                           handshake */
                        return BUFFER_ERROR;
                    }
                }
            #endif
                ssl->arrays->preMasterSz = plainLen;
                ret = MakeMasterSecret(ssl);
            }
            break;
        #endif /* HAVE_NTRU */
        #ifdef HAVE_ECC
            case ecc_diffie_hellman_kea:
            {
                if ((*inOutIdx - begin) + OPAQUE8_LEN > size) {
                    return BUFFER_ERROR;
                }

                length = input[(*inOutIdx)++];

                if ((*inOutIdx - begin) + length > size) {
                    return BUFFER_ERROR;
                }

                if (ssl->peerEccKey == NULL) {
                    /* alloc/init on demand */
                    ssl->peerEccKey = (ecc_key*)XMALLOC(sizeof(ecc_key),
                                              ssl->ctx->heap, DYNAMIC_TYPE_ECC);
                    if (ssl->peerEccKey == NULL) {
                        WOLFSSL_MSG("PeerEccKey Memory error");
                        return MEMORY_E;
                    }
                    wc_ecc_init(ssl->peerEccKey);
                } else if (ssl->peerEccKeyPresent) {  /* don't leak on reuse */
                    wc_ecc_free(ssl->peerEccKey);
                    ssl->peerEccKeyPresent = 0;
                    wc_ecc_init(ssl->peerEccKey);
                }

                if (wc_ecc_import_x963(input + *inOutIdx, length, ssl->peerEccKey)) {
                    return ECC_PEERKEY_ERROR;
                }

                *inOutIdx += length;
                ssl->peerEccKeyPresent = 1;

                length = sizeof(ssl->arrays->preMasterSecret);

                if (ssl->specs.static_ecdh) {
                    ecc_key staticKey;
                    word32 i = 0;

                    wc_ecc_init(&staticKey);
                    ret = wc_EccPrivateKeyDecode(ssl->buffers.key.buffer, &i,
                                           &staticKey, ssl->buffers.key.length);

                    if (ret == 0) {
                        ret = wc_ecc_shared_secret(&staticKey, ssl->peerEccKey,
                                         ssl->arrays->preMasterSecret, &length);
                    }

                    wc_ecc_free(&staticKey);
                }
                else {
                    if (ssl->eccTempKeyPresent == 0) {
                        WOLFSSL_MSG("Ecc ephemeral key not made correctly");
                        ret = ECC_MAKEKEY_ERROR;
                    } else {
                        ret = wc_ecc_shared_secret(ssl->eccTempKey,ssl->peerEccKey,
                                         ssl->arrays->preMasterSecret, &length);
                    }
                }

                if (ret != 0) {
                    return ECC_SHARED_ERROR;
                }

                ssl->arrays->preMasterSz = length;
            #ifdef HAVE_QSH
                if (ssl->options.haveQSH) {
                    /* extension name */
                    ato16(input + *inOutIdx, &name);
                    *inOutIdx += OPAQUE16_LEN;

                    if (name == TLSX_QUANTUM_SAFE_HYBRID) {
                        /* if qshSz is larger than 0 it is the length of
                           buffer used */
                        if ((qshSz = TLSX_QSHCipher_Parse(ssl, input + *inOutIdx,
                                              size - *inOutIdx + begin, 1)) < 0) {
                            return qshSz;
                        }
                        *inOutIdx += qshSz;
                    }
                    else {
                        /* unknown extension sent client ignored
                           handshake */
                        return BUFFER_ERROR;
                    }
                }
            #endif
                ret = MakeMasterSecret(ssl);
            }
            break;
        #endif /* HAVE_ECC */
        #ifndef NO_DH
            case diffie_hellman_kea:
            {
                word16 clientPubSz;
                DhKey  dhKey;

                if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                    return BUFFER_ERROR;
                }

                ato16(input + *inOutIdx, &clientPubSz);
                *inOutIdx += OPAQUE16_LEN;

                if ((*inOutIdx - begin) + clientPubSz > size) {
                    return BUFFER_ERROR;
                }

                wc_InitDhKey(&dhKey);
                ret = wc_DhSetKey(&dhKey, ssl->buffers.serverDH_P.buffer,
                                       ssl->buffers.serverDH_P.length,
                                       ssl->buffers.serverDH_G.buffer,
                                       ssl->buffers.serverDH_G.length);
                if (ret == 0) {
                    ret = wc_DhAgree(&dhKey, ssl->arrays->preMasterSecret,
                                         &ssl->arrays->preMasterSz,
                                          ssl->buffers.serverDH_Priv.buffer,
                                          ssl->buffers.serverDH_Priv.length,
                                          input + *inOutIdx, clientPubSz);
                }
                wc_FreeDhKey(&dhKey);

                *inOutIdx += clientPubSz;

            #ifdef HAVE_QSH
                if (ssl->options.haveQSH) {
                    /* extension name */
                    ato16(input + *inOutIdx, &name);
                    *inOutIdx += OPAQUE16_LEN;

                    if (name == TLSX_QUANTUM_SAFE_HYBRID) {
                        /* if qshSz is larger than 0 it is the length of
                           buffer used */
                        if ((qshSz = TLSX_QSHCipher_Parse(ssl, input + *inOutIdx,
                                              size - *inOutIdx + begin, 1)) < 0) {
                            return qshSz;
                        }
                        *inOutIdx += qshSz;
                    }
                    else {
                        /* unknown extension sent client ignored
                           handshake */
                        return BUFFER_ERROR;
                    }
                }
            #endif
                if (ret == 0) {
                    ret = MakeMasterSecret(ssl);
                }
            }
            break;
        #endif /* NO_DH */
        #if !defined(NO_DH) && !defined(NO_PSK)
            case dhe_psk_kea:
            {
                byte* pms = ssl->arrays->preMasterSecret;
                word16 clientSz;
                DhKey  dhKey;

                /* Read in the PSK hint */
                if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                    return BUFFER_ERROR;
                }

                ato16(input + *inOutIdx, &clientSz);
                *inOutIdx += OPAQUE16_LEN;
                if (clientSz > MAX_PSK_ID_LEN) {
                    return CLIENT_ID_ERROR;
                }

                if ((*inOutIdx - begin) + clientSz > size) {
                    return BUFFER_ERROR;
                }

                XMEMCPY(ssl->arrays->client_identity,
                                                   input + *inOutIdx, clientSz);
                *inOutIdx += clientSz;
                ssl->arrays->client_identity[min(clientSz, MAX_PSK_ID_LEN-1)] =
                                                                              0;

                /* Read in the DHE business */
                if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                    return BUFFER_ERROR;
                }

                ato16(input + *inOutIdx, &clientSz);
                *inOutIdx += OPAQUE16_LEN;

                if ((*inOutIdx - begin) + clientSz > size) {
                    return BUFFER_ERROR;
                }

                wc_InitDhKey(&dhKey);
                ret = wc_DhSetKey(&dhKey, ssl->buffers.serverDH_P.buffer,
                                       ssl->buffers.serverDH_P.length,
                                       ssl->buffers.serverDH_G.buffer,
                                       ssl->buffers.serverDH_G.length);
                if (ret == 0) {
                    ret = wc_DhAgree(&dhKey, pms + OPAQUE16_LEN,
                                          &ssl->arrays->preMasterSz,
                                          ssl->buffers.serverDH_Priv.buffer,
                                          ssl->buffers.serverDH_Priv.length,
                                          input + *inOutIdx, clientSz);
                }
                wc_FreeDhKey(&dhKey);

                *inOutIdx += clientSz;
                c16toa((word16)ssl->arrays->preMasterSz, pms);
                ssl->arrays->preMasterSz += OPAQUE16_LEN;
                pms += ssl->arrays->preMasterSz;

                /* Use the PSK hint to look up the PSK and add it to the
                 * preMasterSecret here. */
                ssl->arrays->psk_keySz = ssl->options.server_psk_cb(ssl,
                    ssl->arrays->client_identity, ssl->arrays->psk_key,
                    MAX_PSK_KEY_LEN);

                if (ssl->arrays->psk_keySz == 0 ||
                                       ssl->arrays->psk_keySz > MAX_PSK_KEY_LEN) {
                    return PSK_KEY_ERROR;
                }

                c16toa((word16) ssl->arrays->psk_keySz, pms);
                pms += OPAQUE16_LEN;

                XMEMCPY(pms, ssl->arrays->psk_key, ssl->arrays->psk_keySz);
                ssl->arrays->preMasterSz +=
                                          ssl->arrays->psk_keySz + OPAQUE16_LEN;
            #ifdef HAVE_QSH
                if (ssl->options.haveQSH) {
                    /* extension name */
                    ato16(input + *inOutIdx, &name);
                    *inOutIdx += OPAQUE16_LEN;

                    if (name == TLSX_QUANTUM_SAFE_HYBRID) {
                        /* if qshSz is larger than 0 it is the length of
                           buffer used */
                        if ((qshSz = TLSX_QSHCipher_Parse(ssl, input + *inOutIdx,
                                              size - *inOutIdx + begin, 1)) < 0) {
                            return qshSz;
                        }
                        *inOutIdx += qshSz;
                    }
                    else {
                        /* unknown extension sent client ignored
                           handshake */
                        return BUFFER_ERROR;
                    }
                }
            #endif
                if (ret == 0)
                    ret = MakeMasterSecret(ssl);

                /* No further need for PSK */
                ForceZero(ssl->arrays->psk_key, ssl->arrays->psk_keySz);
                ssl->arrays->psk_keySz = 0;
            }
            break;
        #endif /* !NO_DH && !NO_PSK */
            default:
            {
                WOLFSSL_MSG("Bad kea type");
                ret = BAD_KEA_TYPE_E;
            }
            break;
        }
