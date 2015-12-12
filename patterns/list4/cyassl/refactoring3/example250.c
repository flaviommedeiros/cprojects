switch (keyOID) {
    #ifndef NO_RSA
        case RSAk:
        {
            word32 idx = 0;
            int    encodedSigSz, verifySz;
            byte*  out;
#ifdef CYASSL_SMALL_STACK
            RsaKey* pubKey;
            byte* plain;
            byte* encodedSig;
#else
            RsaKey pubKey[1];
            byte plain[MAX_ENCODED_SIG_SZ];
            byte encodedSig[MAX_ENCODED_SIG_SZ];
#endif

#ifdef CYASSL_SMALL_STACK
            pubKey = (RsaKey*)XMALLOC(sizeof(RsaKey), NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
            plain = (byte*)XMALLOC(MAX_ENCODED_SIG_SZ, NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
            encodedSig = (byte*)XMALLOC(MAX_ENCODED_SIG_SZ, NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
            
            if (pubKey == NULL || plain == NULL || encodedSig == NULL) {
                CYASSL_MSG("Failed to allocate memory at ConfirmSignature");
                
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
                CYASSL_MSG("Verify Signautre is too big");
            }
            else if (InitRsaKey(pubKey, heap) != 0) {
                CYASSL_MSG("InitRsaKey failed");
            }
            else if (RsaPublicKeyDecode(key, &idx, pubKey, keySz) < 0) {
                CYASSL_MSG("ASN Key decode error RSA");
            }
            else {
                XMEMCPY(plain, sig, sigSz);

                if ((verifySz = RsaSSL_VerifyInline(plain, sigSz, &out,
                                                                 pubKey)) < 0) {
                    CYASSL_MSG("Rsa SSL verify error");
                }
                else {
                    /* make sure we're right justified */
                    encodedSigSz =
                        EncodeSignature(encodedSig, digest, digestSz, typeH);
                    if (encodedSigSz != verifySz ||
                                XMEMCMP(out, encodedSig, encodedSigSz) != 0) {
                        CYASSL_MSG("Rsa SSL verify match encode error");
                    }
                    else
                        ret = 1; /* match */

                    #ifdef CYASSL_DEBUG_ENCODING
                    {
                        int x;
                        
                        printf("cyassl encodedSig:\n");
                        
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
                    #endif /* CYASSL_DEBUG_ENCODING */
                    
                }
                
            }
            
            FreeRsaKey(pubKey);
            
#ifdef CYASSL_SMALL_STACK
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
#ifdef CYASSL_SMALL_STACK
            ecc_key* pubKey;
#else
            ecc_key pubKey[1];
#endif

#ifdef CYASSL_SMALL_STACK
            pubKey = (ecc_key*)XMALLOC(sizeof(ecc_key), NULL,
                                                       DYNAMIC_TYPE_TMP_BUFFER);
            if (pubKey == NULL) {
                CYASSL_MSG("Failed to allocate pubKey");
                break; /* not confirmed */
            }
#endif

            if (ecc_import_x963(key, keySz, pubKey) < 0) {
                CYASSL_MSG("ASN Key import error ECC");
            }
            else {   
                if (ecc_verify_hash(sig, sigSz, digest, digestSz, &verify,
                                                                pubKey) != 0) {
                    CYASSL_MSG("ECC verify hash error");
                }
                else if (1 != verify) {
                    CYASSL_MSG("ECC Verify didn't match");
                } else
                    ret = 1; /* match */

                ecc_free(pubKey);
            }
#ifdef CYASSL_SMALL_STACK
            XFREE(pubKey, NULL, DYNAMIC_TYPE_TMP_BUFFER);
#endif
            break;
        }
    #endif /* HAVE_ECC */
        default:
            CYASSL_MSG("Verify Key type unknown");
    }
