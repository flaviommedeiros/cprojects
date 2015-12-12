if ( (pAdapter->device_mode == WLAN_HDD_INFRA_STATION) 
#ifdef WLAN_FEATURE_P2P
            || (pAdapter->device_mode == WLAN_HDD_P2P_CLIENT)
#endif
            )
    {
        hdd_wext_state_t *pWextState = WLAN_HDD_GET_WEXT_STATE_PTR(pAdapter);
        hdd_station_ctx_t *pHddStaCtx = WLAN_HDD_GET_STATION_CTX_PTR(pAdapter);

        pWextState->roamProfile.Keys.KeyLength[key_index] = (u8)params->key_len;

        vos_mem_copy(&pWextState->roamProfile.Keys.KeyMaterial[key_index][0], 
                params->key, params->key_len);

        pHddStaCtx->roam_info.roamingState = HDD_ROAM_STATE_SETTING_KEY;

    if (!(  ( IW_AUTH_KEY_MGMT_802_1X 
                    == (pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_802_1X)) 
                    && (eCSR_AUTH_TYPE_OPEN_SYSTEM == pHddStaCtx->conn_info.authType)
             )
                &&
                (  (WLAN_CIPHER_SUITE_WEP40 == params->cipher)
                   || (WLAN_CIPHER_SUITE_WEP104 == params->cipher)
                )
           )
        {
            /* in case of static WEP, macaddr/bssid is not coming from nl80211
             * interface, copy bssid for pairwise key and group macaddr for 
             * group key initialization*/

            tCsrRoamProfile          *pRoamProfile = &pWextState->roamProfile;

            pWextState->roamProfile.negotiatedUCEncryptionType = 
                pHddStaCtx->conn_info.ucEncryptionType = 
                ((WLAN_CIPHER_SUITE_WEP40 == params->cipher) ?
                 eCSR_ENCRYPT_TYPE_WEP40_STATICKEY :
                 eCSR_ENCRYPT_TYPE_WEP104_STATICKEY);


            hddLog(VOS_TRACE_LEVEL_INFO_MED, 
                    "%s: Negotiated encryption type %d", __func__, 
                    pWextState->roamProfile.negotiatedUCEncryptionType);

            sme_SetCfgPrivacy((tpAniSirGlobal)WLAN_HDD_GET_HAL_CTX(pAdapter),
                    &pWextState->roamProfile, true);
            setKey.keyLength = 0;
            setKey.keyDirection =  eSIR_TX_RX;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38))
            if (pairwise) 
            {
#endif
                if (mac_addr)
                {
                    vos_mem_copy(setKey.peerMac, mac_addr,WNI_CFG_BSSID_LEN);
                }
                else
                {
                    /* macaddr is NULL, set the peerMac to bssId in case of BSS, 
                     * and peerMacAddress in case of IBSS*/
                    if (eCSR_BSS_TYPE_START_IBSS == pRoamProfile->BSSType)
                    {
                        u8 staidx = wlan_hdd_cfg80211_get_ibss_peer_staidx(pAdapter);
                        if (HDD_MAX_NUM_IBSS_STA != staidx)
                        {
                            vos_mem_copy(setKey.peerMac,
                                    &pHddStaCtx->conn_info.peerMacAddress[staidx],
                                    WNI_CFG_BSSID_LEN);

                        } 
                        else
                        {
                            hddLog(VOS_TRACE_LEVEL_ERROR, "%s: No peerMac found", 
                                    __func__);
                            return -EOPNOTSUPP;
                        } 
                    }
                    else
                    {
                        vos_mem_copy(setKey.peerMac,
                                &pHddStaCtx->conn_info.bssId[0],
                                WNI_CFG_BSSID_LEN);
                    }
                }
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38))
            }
            else
            {
                /* set group key*/
                VOS_TRACE( VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,
                        "%s- %d: setting Group key",
                        __func__, __LINE__);
                setKey.keyDirection = eSIR_RX_ONLY;
                vos_mem_copy(setKey.peerMac, groupmacaddr, WNI_CFG_BSSID_LEN);
            }
#endif
        }
        else if (
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38))
                (!pairwise)
#else
                (!mac_addr || is_broadcast_ether_addr(mac_addr)) 
#endif
                )
        {
            /* set group key*/
            VOS_TRACE( VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,
                    "%s- %d: setting Group key",
                    __func__, __LINE__);
            setKey.keyDirection = eSIR_RX_ONLY;
            vos_mem_copy(setKey.peerMac,groupmacaddr,WNI_CFG_BSSID_LEN);
        }
        else
        {
            /* set pairwise key*/
            VOS_TRACE( VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,
                    "%s- %d: setting pairwise key",
                    __func__, __LINE__);
            setKey.keyDirection = eSIR_TX_RX;
            vos_mem_copy(setKey.peerMac, mac_addr,WNI_CFG_BSSID_LEN);
        }

        hddLog(VOS_TRACE_LEVEL_INFO_MED, 
                "%s: set key for peerMac %2x:%2x:%2x:%2x:%2x:%2x, direction %d",
                __func__, setKey.peerMac[0], setKey.peerMac[1], 
                setKey.peerMac[2], setKey.peerMac[3], 
                setKey.peerMac[4], setKey.peerMac[5], 
                setKey.keyDirection);

        vos_status = wlan_hdd_check_ula_done(pAdapter);

        if ( vos_status != VOS_STATUS_SUCCESS )
        {
            VOS_TRACE( VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_ERROR,
                    "[%4d] wlan_hdd_check_ula_done returned ERROR status= %d",
                    __LINE__, vos_status );

            pHddStaCtx->roam_info.roamingState = HDD_ROAM_STATE_NONE;

            return -EINVAL;

        }


        /* issue set key request to SME*/
        status = sme_RoamSetKey( WLAN_HDD_GET_HAL_CTX(pAdapter),
                pAdapter->sessionId, &setKey, &roamId );

        if ( 0 != status )
        {
            hddLog(VOS_TRACE_LEVEL_ERROR, 
                    "%s: sme_RoamSetKey failed, returned %d", __func__, status);
            pHddStaCtx->roam_info.roamingState = HDD_ROAM_STATE_NONE;
            return -EINVAL;
        }


        /* in case of IBSS as there was no information available about WEP keys during 
         * IBSS join, group key intialized with NULL key, so re-initialize group key 
         * with correct value*/
        if ( (eCSR_BSS_TYPE_START_IBSS == pWextState->roamProfile.BSSType) && 
            !(  ( IW_AUTH_KEY_MGMT_802_1X 
                    == (pWextState->authKeyMgmt & IW_AUTH_KEY_MGMT_802_1X)) 
                    && (eCSR_AUTH_TYPE_OPEN_SYSTEM == pHddStaCtx->conn_info.authType)
                 )
                &&
                (  (WLAN_CIPHER_SUITE_WEP40 == params->cipher)
                   || (WLAN_CIPHER_SUITE_WEP104 == params->cipher)
                )
           )
        {
            setKey.keyDirection = eSIR_RX_ONLY;
            vos_mem_copy(setKey.peerMac,groupmacaddr,WNI_CFG_BSSID_LEN);

            hddLog(VOS_TRACE_LEVEL_INFO_MED, 
                    "%s: set key peerMac %2x:%2x:%2x:%2x:%2x:%2x, direction %d",
                    __func__, setKey.peerMac[0], setKey.peerMac[1], 
                    setKey.peerMac[2], setKey.peerMac[3], 
                    setKey.peerMac[4], setKey.peerMac[5], 
                    setKey.keyDirection);

            status = sme_RoamSetKey( WLAN_HDD_GET_HAL_CTX(pAdapter), 
                    pAdapter->sessionId, &setKey, &roamId );

            if ( 0 != status )
            {
                hddLog(VOS_TRACE_LEVEL_ERROR, 
                        "%s: sme_RoamSetKey failed for group key (IBSS), returned %d", 
                        __func__, status);
                pHddStaCtx->roam_info.roamingState = HDD_ROAM_STATE_NONE;
                return -EINVAL;
            }
        }
    }
