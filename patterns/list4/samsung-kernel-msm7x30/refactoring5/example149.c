#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
                {   
                    tpSirKeys pKey;
                    pKey =  &psessionEntry->WEPKeyMaterial[keyId].key[0];              
                    palCopyMemory( pMac->hHdd, defaultKey, pKey->key, pKey->keyLength);
                    val = pKey->keyLength;
                }                   
                else                              
#endif                                    
                if (wlan_cfgGetStr(pMac, (tANI_U16) (WNI_CFG_WEP_DEFAULT_KEY_1 + keyId),
                              defaultKey, &val) != eSIR_SUCCESS)
                {
                    /// Could not get Default key from CFG.
                    //Log error.
                    limLog(pMac, LOGP,
                           FL("could not retrieve Default key\n"));

                    /**
                     * Send Authentication frame
                     * with challenge failure status code
                     */

                    authFrame.authAlgoNumber = eSIR_SHARED_KEY;
                    authFrame.authTransactionSeqNumber =
                    SIR_MAC_AUTH_FRAME_4;
                    authFrame.authStatusCode =
                    eSIR_MAC_CHALLENGE_FAILURE_STATUS;

                    limSendAuthMgmtFrame(pMac, &authFrame,
                                         pHdr->sa,
                                         LIM_NO_WEP_IN_FC,psessionEntry);

                    return;
                }
