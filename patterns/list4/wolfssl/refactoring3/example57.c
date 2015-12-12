switch (ssl->specs.kea)
        {
    #ifndef NO_PSK
        case psk_kea:
        {
            if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                return BUFFER_ERROR;
            }

            ato16(input + *inOutIdx, &length);
            *inOutIdx += OPAQUE16_LEN;

            if ((*inOutIdx - begin) + length > size) {
                return BUFFER_ERROR;
            }

            XMEMCPY(ssl->arrays->server_hint, input + *inOutIdx,
                   min(length, MAX_PSK_ID_LEN));

            ssl->arrays->server_hint[min(length, MAX_PSK_ID_LEN - 1)] = 0;
            *inOutIdx += length;

            /* QSH extensions */
        #ifdef HAVE_QSH
            if (ssl->peerQSHKeyPresent) {
                /* extension name */
                ato16(input + *inOutIdx, &name);
                *inOutIdx += OPAQUE16_LEN;

                if (name == TLSX_QUANTUM_SAFE_HYBRID) {
                    /* if qshSz is larger than 0 it is the length of buffer
                       used */
                    if ((qshSz = TLSX_QSHCipher_Parse(ssl, input + *inOutIdx,
                                                               size, 0)) < 0) {
                        return qshSz;
                    }
                    *inOutIdx += qshSz;
                }
                else {
                    /* unknown extension sent server ignored
                       handshake */
                    return BUFFER_ERROR;
                }
            }
        #endif

            return 0;
        }
    #endif
    #ifndef NO_DH
        case diffie_hellman_kea:
        {
            /* p */
            if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                return BUFFER_ERROR;
            }

            ato16(input + *inOutIdx, &length);
            *inOutIdx += OPAQUE16_LEN;

            if ((*inOutIdx - begin) + length > size) {
                return BUFFER_ERROR;
            }

            if (length < ssl->options.minDhKeySz) {
                WOLFSSL_MSG("Server using a DH key that is too small");
                SendAlert(ssl, alert_fatal, handshake_failure);
                return DH_KEY_SIZE_E;
            }

            ssl->buffers.serverDH_P.buffer = (byte*) XMALLOC(length, ssl->heap,
                                                             DYNAMIC_TYPE_DH);

            if (ssl->buffers.serverDH_P.buffer) {
                ssl->buffers.serverDH_P.length = length;
            }
            else {
                return MEMORY_ERROR;
            }

            XMEMCPY(ssl->buffers.serverDH_P.buffer, input + *inOutIdx, length);
            *inOutIdx += length;

            ssl->options.dhKeySz = length;

            /* g */
            if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                return BUFFER_ERROR;
            }

            ato16(input + *inOutIdx, &length);
            *inOutIdx += OPAQUE16_LEN;

            if ((*inOutIdx - begin) + length > size) {
                return BUFFER_ERROR;
            }

            ssl->buffers.serverDH_G.buffer = (byte*) XMALLOC(length, ssl->heap,
                                                             DYNAMIC_TYPE_DH);

            if (ssl->buffers.serverDH_G.buffer) {
                ssl->buffers.serverDH_G.length = length;
            }
            else {
                return MEMORY_ERROR;
            }

            XMEMCPY(ssl->buffers.serverDH_G.buffer, input + *inOutIdx, length);
            *inOutIdx += length;

            /* pub */
            if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
                return BUFFER_ERROR;
            }

            ato16(input + *inOutIdx, &length);
            *inOutIdx += OPAQUE16_LEN;

            if ((*inOutIdx - begin) + length > size) {
                return BUFFER_ERROR;
            }

            ssl->buffers.serverDH_Pub.buffer = 
                (byte*) XMALLOC(length, ssl->heap, DYNAMIC_TYPE_DH);

            if (ssl->buffers.serverDH_Pub.buffer) {
                ssl->buffers.serverDH_Pub.length = length;
            }
            else {
                return MEMORY_ERROR;
            }

            XMEMCPY(ssl->buffers.serverDH_Pub.buffer, input + *inOutIdx, 
                length);
            *inOutIdx += length;
            break;
        }  /* dh_kea */
    #endif /* NO_DH */

    #ifdef HAVE_ECC
        case ecc_diffie_hellman_kea:
        {
            byte b;

            if ((*inOutIdx - begin) + ENUM_LEN + OPAQUE16_LEN + 
                OPAQUE8_LEN > size) {
                return BUFFER_ERROR;
            }

            b = input[(*inOutIdx)++];

            if (b != named_curve) {
                return ECC_CURVETYPE_ERROR;
            }

            *inOutIdx += 1;   /* curve type, eat leading 0 */
            b = input[(*inOutIdx)++];

            if (CheckCurveId(b) != 0) {
                return ECC_CURVE_ERROR;
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

            if (wc_ecc_import_x963(input + *inOutIdx, length, 
                ssl->peerEccKey) != 0) {
                return ECC_PEERKEY_ERROR;
            }

            *inOutIdx += length;
            ssl->peerEccKeyPresent = 1;

            break;
        }
    #endif /* HAVE_ECC */

    #if !defined(NO_DH) && !defined(NO_PSK)
    case dhe_psk_kea:
    {
        if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
            return BUFFER_ERROR;
        }

        ato16(input + *inOutIdx, &length);
        *inOutIdx += OPAQUE16_LEN;

        if ((*inOutIdx - begin) + length > size) {
            return BUFFER_ERROR;
        }

        XMEMCPY(ssl->arrays->server_hint, input + *inOutIdx,
            min(length, MAX_PSK_ID_LEN));

        ssl->arrays->server_hint[min(length, MAX_PSK_ID_LEN - 1)] = 0;
        *inOutIdx += length;

        /* p */
        if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
            return BUFFER_ERROR;
        }

        ato16(input + *inOutIdx, &length);
        *inOutIdx += OPAQUE16_LEN;

        if ((*inOutIdx - begin) + length > size) {
            return BUFFER_ERROR;
        }

        if (length < ssl->options.minDhKeySz) {
            WOLFSSL_MSG("Server using a DH key that is too small");
            SendAlert(ssl, alert_fatal, handshake_failure);
            return DH_KEY_SIZE_E;
        }

        ssl->buffers.serverDH_P.buffer = (byte*) XMALLOC(length, ssl->heap, 
                                                         DYNAMIC_TYPE_DH);

        if (ssl->buffers.serverDH_P.buffer) {
            ssl->buffers.serverDH_P.length = length;
        }
        else {
            return MEMORY_ERROR;
        }

        XMEMCPY(ssl->buffers.serverDH_P.buffer, input + *inOutIdx, length);
        *inOutIdx += length;

        ssl->options.dhKeySz = length;

        /* g */
        if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
            return BUFFER_ERROR;
        }

        ato16(input + *inOutIdx, &length);
        *inOutIdx += OPAQUE16_LEN;

        if ((*inOutIdx - begin) + length > size) {
            return BUFFER_ERROR;
        }

        ssl->buffers.serverDH_G.buffer = (byte*) XMALLOC(length, ssl->heap,
                                                         DYNAMIC_TYPE_DH);

        if (ssl->buffers.serverDH_G.buffer) {
            ssl->buffers.serverDH_G.length = length;
        }
        else {
            return MEMORY_ERROR;
        }

        XMEMCPY(ssl->buffers.serverDH_G.buffer, input + *inOutIdx, length);
        *inOutIdx += length;

        /* pub */
        if ((*inOutIdx - begin) + OPAQUE16_LEN > size) {
            return BUFFER_ERROR;
        }

        ato16(input + *inOutIdx, &length);
        *inOutIdx += OPAQUE16_LEN;

        if ((*inOutIdx - begin) + length > size) {
            return BUFFER_ERROR;
        }

        ssl->buffers.serverDH_Pub.buffer = (byte*) XMALLOC(length, ssl->heap,
                                                           DYNAMIC_TYPE_DH);

        if (ssl->buffers.serverDH_Pub.buffer) {
            ssl->buffers.serverDH_Pub.length = length;
        }
        else {
            return MEMORY_ERROR;
        }

        XMEMCPY(ssl->buffers.serverDH_Pub.buffer, input + *inOutIdx, length);
        *inOutIdx += length;

        break;
    }
    #endif /* !NO_DH || !NO_PSK */
    }
