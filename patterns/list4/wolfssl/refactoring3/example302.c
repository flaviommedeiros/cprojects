switch (cert->keyOID) {
   #ifndef NO_RSA
        case RSAk:
        {
            byte b = cert->source[cert->srcIdx++];
            if (b != ASN_BIT_STRING)
                return ASN_BITSTR_E;

            if (GetLength(cert->source,&cert->srcIdx,&length,cert->maxIdx) < 0)
                return ASN_PARSE_E;
            b = cert->source[cert->srcIdx++];
            if (b != 0x00)
                return ASN_EXPECT_0_E;

            return StoreRsaKey(cert);
        }

    #endif /* NO_RSA */
    #ifdef HAVE_NTRU
        case NTRUk:
        {
            const byte* key = &cert->source[tmpIdx];
            byte*       next = (byte*)key;
            word16      keyLen;
            word32      rc;
            word32      remaining = cert->maxIdx - cert->srcIdx;
#ifdef WOLFSSL_SMALL_STACK
            byte*       keyBlob = NULL;
#else
            byte        keyBlob[MAX_NTRU_KEY_SZ];
#endif
            rc = ntru_crypto_ntru_encrypt_subjectPublicKeyInfo2PublicKey(key,
                                &keyLen, NULL, &next, &remaining);
            if (rc != NTRU_OK)
                return ASN_NTRU_KEY_E;
            if (keyLen > MAX_NTRU_KEY_SZ)
                return ASN_NTRU_KEY_E;

#ifdef WOLFSSL_SMALL_STACK
            keyBlob = (byte*)XMALLOC(MAX_NTRU_KEY_SZ, NULL,
                                     DYNAMIC_TYPE_TMP_BUFFER);
            if (keyBlob == NULL)
                return MEMORY_E;
#endif

            rc = ntru_crypto_ntru_encrypt_subjectPublicKeyInfo2PublicKey(key,
                                &keyLen, keyBlob, &next, &remaining);
            if (rc != NTRU_OK) {
#ifdef WOLFSSL_SMALL_STACK
                XFREE(keyBlob, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
                return ASN_NTRU_KEY_E;
            }

            if ( (next - key) < 0) {
#ifdef WOLFSSL_SMALL_STACK
                XFREE(keyBlob, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
                return ASN_NTRU_KEY_E;
            }

            cert->srcIdx = tmpIdx + (int)(next - key);

            cert->publicKey = (byte*) XMALLOC(keyLen, cert->heap,
                                              DYNAMIC_TYPE_PUBLIC_KEY);
            if (cert->publicKey == NULL) {
#ifdef WOLFSSL_SMALL_STACK
                XFREE(keyBlob, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
                return MEMORY_E;
            }
            XMEMCPY(cert->publicKey, keyBlob, keyLen);
            cert->pubKeyStored = 1;
            cert->pubKeySize   = keyLen;

#ifdef WOLFSSL_SMALL_STACK
            XFREE(keyBlob, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif

            return 0;
        }
    #endif /* HAVE_NTRU */
    #ifdef HAVE_ECC
        case ECDSAk:
        {
            byte b;

            if (GetObjectId(cert->source, &cert->srcIdx,
                            &cert->pkCurveOID, curveType, cert->maxIdx) < 0)
                return ASN_PARSE_E;

            if (CheckCurve(cert->pkCurveOID) < 0)
                return ECC_CURVE_OID_E;

            /* key header */
            b = cert->source[cert->srcIdx++];
            if (b != ASN_BIT_STRING)
                return ASN_BITSTR_E;

            if (GetLength(cert->source,&cert->srcIdx,&length,cert->maxIdx) < 0)
                return ASN_PARSE_E;
            b = cert->source[cert->srcIdx++];
            if (b != 0x00)
                return ASN_EXPECT_0_E;

            /* actual key, use length - 1 since ate preceding 0 */
            length -= 1;

            cert->publicKey = (byte*) XMALLOC(length, cert->heap,
                                              DYNAMIC_TYPE_PUBLIC_KEY);
            if (cert->publicKey == NULL)
                return MEMORY_E;
            XMEMCPY(cert->publicKey, &cert->source[cert->srcIdx], length);
            cert->pubKeyStored = 1;
            cert->pubKeySize   = length;

            cert->srcIdx += length;

            return 0;
        }
    #endif /* HAVE_ECC */
        default:
            return ASN_UNKNOWN_OID_E;
    }
