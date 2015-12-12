switch ( ucCipher )
        {
            case eCSR_ENCRYPT_TYPE_NONE:
                {
                    // for NO encryption, if the Bss description has the Privacy bit turned on, then encryption is
                    // required so we have to reject this Bss.
                    if ( csrIsPrivacy( pSirBssDesc ) )
                    {
                        fMatch = FALSE;
                    }
                    else
                    {
                        fMatch = TRUE;
                    }

                    if ( fMatch )
                    {
                        fMatch = FALSE;
                        //Check Multicast cipher requested and Auth type requested.
                        for( idx = 0 ; idx < pMCEncryptionType->numEntries ; idx++ )
                        {
                            if( eCSR_ENCRYPT_TYPE_NONE == pMCEncryptionType->encryptionType[idx] )
                            {
                                fMatch = TRUE; //Multicast can only be none.
                                mcCipher = pMCEncryptionType->encryptionType[idx];
                                break;
                            }
                        }
                        if (!fMatch) break;

                        fMatch = FALSE;
                        //Check Auth list. It should contain AuthOpen.
                        for( idx = 0 ; idx < authType->numEntries ; idx++ )
                        {
                            if( eCSR_AUTH_TYPE_OPEN_SYSTEM == authType->authType[idx] )
                            {
                               fMatch = TRUE;
                               negAuthType = eCSR_AUTH_TYPE_OPEN_SYSTEM;
                               break;
                            }
                        } 
                        if (!fMatch) break;

                    }
                    break;
                }

            case eCSR_ENCRYPT_TYPE_WEP40_STATICKEY:
            case eCSR_ENCRYPT_TYPE_WEP104_STATICKEY:
                // !! might want to check for WEP keys set in the Profile.... ?
                // !! don't need to have the privacy bit in the Bss description.  Many AP policies make legacy
                // encryption 'optional' so we don't know if we can associate or not.  The AP will reject if
                // encryption is not allowed without the Privacy bit turned on.
                fMatch = csrValidateWep( pMac, ucCipher, authType, pMCEncryptionType, &negAuthType, &mcCipher, pSirBssDesc, pIes);

                break;

                // these are all of the WPA encryption types...
            case eCSR_ENCRYPT_TYPE_WEP40:
            case eCSR_ENCRYPT_TYPE_WEP104:
                fMatch = csrValidateWep( pMac, ucCipher, authType, pMCEncryptionType, &negAuthType, &mcCipher, pSirBssDesc, pIes);
                break;

            case eCSR_ENCRYPT_TYPE_TKIP:
            case eCSR_ENCRYPT_TYPE_AES:
                {
                    if(pIes)
                    {
                        // First check if there is a RSN match
                        fMatch = csrIsRSNMatch( pMac, authType, ucCipher, pMCEncryptionType, pIes, &negAuthType, &mcCipher );
                        if( !fMatch )
                        {
                            // If not RSN, then check if there is a WPA match
                            fMatch = csrIsWpaEncryptionMatch( pMac, authType, ucCipher, pMCEncryptionType, pIes, 
                                                              &negAuthType, &mcCipher );
                        }
                    }
                    else
                    {
                        fMatch = FALSE;
                    }
                    break;
                }
#ifdef FEATURE_WLAN_WAPI
           case eCSR_ENCRYPT_TYPE_WPI://WAPI
               {
                   if(pIes)
                   {
                       fMatch = csrIsWapiMatch( hHal, authType, ucCipher, pMCEncryptionType, pIes, &negAuthType, &mcCipher );
                   }
                   else
                   {
                       fMatch = FALSE;
                   }
                   break;
               }
#endif /* FEATURE_WLAN_WAPI */
            case eCSR_ENCRYPT_TYPE_ANY: 
            default: 
            {
                tANI_BOOLEAN fMatchAny = eANI_BOOLEAN_FALSE;

                fMatch = eANI_BOOLEAN_TRUE;
                //It is allowed to match anything. Try the more secured ones first.
                if(pIes)
                {
                    //Check AES first
                    ucCipher = eCSR_ENCRYPT_TYPE_AES;
                    fMatchAny = csrIsRSNMatch( hHal, authType, ucCipher, pMCEncryptionType, pIes, &negAuthType, &mcCipher );
                    if(!fMatchAny)
                    {
                        //Check TKIP
                        ucCipher = eCSR_ENCRYPT_TYPE_TKIP;
                        fMatchAny = csrIsRSNMatch( hHal, authType, ucCipher, pMCEncryptionType, pIes, &negAuthType, &mcCipher );
                    }
#ifdef FEATURE_WLAN_WAPI
                    if(!fMatchAny)
                    {
                        //Check WAPI
                        ucCipher = eCSR_ENCRYPT_TYPE_WPI;
                        fMatchAny = csrIsWapiMatch( hHal, authType, ucCipher, pMCEncryptionType, pIes, &negAuthType, &mcCipher );
                    }
#endif /* FEATURE_WLAN_WAPI */
                }
                if(!fMatchAny)
                {
                    ucCipher = eCSR_ENCRYPT_TYPE_WEP104;
                    if(!csrValidateWep( pMac, ucCipher, authType, pMCEncryptionType, &negAuthType, &mcCipher, pSirBssDesc, pIes))
                    {
                        ucCipher = eCSR_ENCRYPT_TYPE_WEP40;
                        if(!csrValidateWep( pMac, ucCipher, authType, pMCEncryptionType, &negAuthType, &mcCipher, pSirBssDesc, pIes))
                        {
                            ucCipher = eCSR_ENCRYPT_TYPE_WEP104_STATICKEY;
                            if(!csrValidateWep( pMac, ucCipher, authType, pMCEncryptionType, &negAuthType, &mcCipher, pSirBssDesc, pIes))
                            {
                                ucCipher = eCSR_ENCRYPT_TYPE_WEP40_STATICKEY;
                                if(!csrValidateWep( pMac, ucCipher, authType, pMCEncryptionType, &negAuthType, &mcCipher, pSirBssDesc, pIes))
                                {
                                    //It must be open and no encryption
                                    if ( csrIsPrivacy( pSirBssDesc ) )
                                    {
                                        //This is not right
                                        fMatch = eANI_BOOLEAN_FALSE;
                                    }
                                    else
                                    {
                                        negAuthType = eCSR_AUTH_TYPE_OPEN_SYSTEM;
                                        mcCipher = eCSR_ENCRYPT_TYPE_NONE;
                                        ucCipher = eCSR_ENCRYPT_TYPE_NONE;
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            }
        }
