switch (keyOID) {
    #ifndef NO_RSA
        case RSAk:
        {
            word32 idx = 0;
            int    encodedSigSz, verifySz;
            byte*  out;
#ifdef WOLFSSL_SMALL_STACK
            RsaKey* pubKey;
            byte* plain;
            byte* encodedSig;
#else
            RsaKey pubKey[1];
            byte plain[MAX_ENCODED_SIG_SZ];
            byte encodedSig[MAX_ENCODED_SIG_SZ];
#endif

#ifdef WOLFSSL_SMALL_STACK
            pubKey = (RsaKey*)XMALLOC(sizeof(RsaKey), NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
            plain = (byte*)XMALLOC(MAX_ENCODED_SIG_SZ, NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
            encodedSig = (byte*)XMALLOC(MAX_ENCODED_SIG_SZ, NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);

            if (pubKey == NULL || plain == NULL || encodedSig == NULL) {
                WOLFSSL_MSG("Failed to allocate memory at ConfirmSignature");

                if (pubKey)
                    XFREE(pubKey, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                if (plain)
                    XFREE(plain, NULL, DYNAMIC_TYPE_TMP_BUFFER);
                if (encodedSig)
                    XFREE(encodedSig, NULL, DYNAMIC_TYPE_TMP_BUFFER);

                break; /* not confirmed */
            }
#endif

            if (sigSz > MAX_ENCODED_SIG_SZ) {
                WOLFSSL_MSG("Verify Signautre is too big");
            }
            else if (wc_InitRsaKey(pubKey, heap) != 0) {
                WOLFSSL_MSG("InitRsaKey failed");
            }
            else if (wc_RsaPublicKeyDecode(key, &idx, pubKey, keySz) < 0) {
                WOLFSSL_MSG("ASN Key decode error RSA");
            }
            else {
                XMEMCPY(plain, sig, sigSz);

                if ((verifySz = wc_RsaSSL_VerifyInline(plain, sigSz, &out,
                                                                 pubKey)) < 0) {
                    WOLFSSL_MSG("Rsa SSL verify error");
                }
                else {
                    /* make sure we're right justified */
                    encodedSigSz =
                        wc_EncodeSignature(encodedSig, digest, digestSz, typeH);
                    if (encodedSigSz != verifySz ||
                                XMEMCMP(out, encodedSig, encodedSigSz) != 0) {
                        WOLFSSL_MSG("Rsa SSL verify match encode error");
                    }
                    else
                        ret = 1; /* match */

                    #ifdef WOLFSSL_DEBUG_ENCODING
                    {
                        int x;

                        printf("wolfssl encodedSig:\n");

                        for (x = 0; x < encodedSigSz; x++) {
                            printf("%02x ", encodedSig[x]);
                            if ( (x % 16) == 15)
                                printf("\n");
                        }

                        printf("\n");
                        printf("actual digest:\n");

                        for (x = 0; x < verifySz; x++) {
                            printf("%02x ", out[x]);
                            if ( (x % 16) == 15)
                                printf("\n");
                        }

                        printf("\n");
                    }
                    #endif /* WOLFSSL_DEBUG_ENCODING */

                }

            }

            wc_FreeRsaKey(pubKey);

#ifdef WOLFSSL_SMALL_STACK
            XFREE(pubKey,     NULL, DYNAMIC_TYPE_TMP_BUFFER);
            XFREE(plain,      NULL, DYNAMIC_TYPE_TMP_BUFFER);
            XFREE(encodedSig, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
            break;
        }

    #endif /* NO_RSA */
    #ifdef HAVE_ECC
        case ECDSAk:
        {
            int verify = 0;
#ifdef WOLFSSL_SMALL_STACK
            ecc_key* pubKey;
#else
            ecc_key pubKey[1];
#endif

#ifdef WOLFSSL_SMALL_STACK
            pubKey = (ecc_key*)XMALLOC(sizeof(ecc_key), NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
            if (pubKey == NULL) {
                WOLFSSL_MSG("Failed to allocate pubKey");
                break; /* not confirmed */
            }
#endif

            if (wc_ecc_init(pubKey) < 0) {
                WOLFSSL_MSG("Failed to initialize key");
                break; /* not confirmed */
            }
            if (wc_ecc_import_x963(key, keySz, pubKey) < 0) {
                WOLFSSL_MSG("ASN Key import error ECC");
            }
            else {
                if (wc_ecc_verify_hash(sig, sigSz, digest, digestSz, &verify,
                                                                pubKey) != 0) {
                    WOLFSSL_MSG("ECC verify hash error");
                }
                else if (1 != verify) {
                    WOLFSSL_MSG("ECC Verify didn't match");
                } else
                    ret = 1; /* match */

            }
            wc_ecc_free(pubKey);

#ifdef WOLFSSL_SMALL_STACK
            XFREE(pubKey, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
            break;
        }
    #endif /* HAVE_ECC */
        default:
            WOLFSSL_MSG("Verify Key type unknown");
    }
