if ((pAdapter->device_mode == WLAN_HDD_INFRA_STATION)
#ifdef WLAN_FEATURE_P2P
     || (pAdapter->device_mode == WLAN_HDD_P2P_CLIENT)
#endif
       ) 
    {
        if ( (key_index != pWextState->roamProfile.Keys.defaultIndex) && 
             (eCSR_ENCRYPT_TYPE_TKIP != 
                pWextState->roamProfile.EncryptionType.encryptionType[0]) &&
             (eCSR_ENCRYPT_TYPE_AES != 
                pWextState->roamProfile.EncryptionType.encryptionType[0])
           )
        {  
            /* if default key index is not same as previous one, 
             * then update the default key index */
    
            tCsrRoamSetKey  setKey;
            v_U32_t roamId= 0xFF;
            tCsrKeys *Keys = &pWextState->roamProfile.Keys;
            
            hddLog(VOS_TRACE_LEVEL_INFO_HIGH, "%s: default tx key index %d", 
                    __func__, key_index);
            
            Keys->defaultIndex = (u8)key_index;
            vos_mem_zero(&setKey,sizeof(tCsrRoamSetKey));
            setKey.keyId = key_index;
            setKey.keyLength = Keys->KeyLength[key_index];
            
            vos_mem_copy(&setKey.Key[0], 
                    &Keys->KeyMaterial[key_index][0], 
                    Keys->KeyLength[key_index]);
    
            setKey.keyDirection = eSIR_TX_ONLY;
    
            vos_mem_copy(setKey.peerMac, 
                    &pHddStaCtx->conn_info.bssId[0],
                    WNI_CFG_BSSID_LEN);
    
            setKey.encType = 
                pWextState->roamProfile.EncryptionType.encryptionType[0];
             
            /* issue set key request */
            status = sme_RoamSetKey( WLAN_HDD_GET_HAL_CTX(pAdapter), 
                                   pAdapter->sessionId, &setKey, &roamId );
    
            if ( 0 != status )
            {
                hddLog(VOS_TRACE_LEVEL_ERROR, 
                        "%s: sme_RoamSetKey failed, returned %d", __func__, 
                        status);
                return -EINVAL;
            }
        }
    }

    /* In SoftAp mode setting key direction for default mode */
    else if ( WLAN_HDD_SOFTAP == pAdapter->device_mode )
    {
        if ( (eCSR_ENCRYPT_TYPE_TKIP !=
                pWextState->roamProfile.EncryptionType.encryptionType[0]) &&
             (eCSR_ENCRYPT_TYPE_AES !=
                pWextState->roamProfile.EncryptionType.encryptionType[0])
           )
        {
            /*  Saving key direction for default key index to TX default */
            hdd_ap_ctx_t *pAPCtx = WLAN_HDD_GET_AP_CTX_PTR(pAdapter);
            pAPCtx->wepKey[key_index].keyDirection = eSIR_TX_DEFAULT;
        }
    }
