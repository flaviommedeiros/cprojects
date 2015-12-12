switch( roamStatus )
    {
        case eCSR_ROAM_SESSION_OPENED:
            if(pAdapter != NULL)
            {
                set_bit(SME_SESSION_OPENED, &pAdapter->event_flags);
                complete(&pAdapter->session_open_comp_var);
            }
            break;
            
#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_CCX) || defined(FEATURE_WLAN_LFR)
            /* We did pre-auth,then we attempted a 11r or ccx reassoc.
             * reassoc failed due to failure, timeout, reject from ap
             * in any case tell the OS, our carrier is off and mark 
             * interface down */
        case eCSR_ROAM_FT_REASSOC_FAILED:
            hddLog(LOG1, FL("Reassoc Failed\n"));
            halStatus = hdd_DisConnectHandler( pAdapter, pRoamInfo, roamId, roamStatus, roamResult );
            /* Check if Mcast/Bcast Filters are set, if yes clear the filters here */
            if ((WLAN_HDD_GET_CTX(pAdapter))->hdd_mcastbcast_filter_set == TRUE) {
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
#ifdef MSM_PLATFORM
                    hdd_conf_mcastbcast_filter((WLAN_HDD_GET_CTX(pAdapter)), FALSE);
#endif
#endif
                    (WLAN_HDD_GET_CTX(pAdapter))->hdd_mcastbcast_filter_set = FALSE;
            }
            pHddStaCtx->ft_carrier_on = FALSE;
            break;

        case eCSR_ROAM_FT_START:
            // When we roam for CCX and 11r, we dont want the 
            // OS to be informed that the link is down. So mark
            // the link ready for ft_start. After this the 
            // eCSR_ROAM_SHOULD_ROAM will be received.
            // Where in we will not mark the link down
            // Also we want to stop tx at this point when we will be
            // doing disassoc at this time. This saves 30-60 msec
            // after reassoc.
            {
                struct net_device *dev = pAdapter->dev;
                netif_tx_disable(dev);
                /*
        		 * Deregister for this STA with TL with the objective to flush
        		 * all the packets for this STA from wmm_tx_queue. If not done here,
        		 * we would run into a race condition (CR390567) wherein TX
        		 * thread would schedule packets from wmm_tx_queue AFTER peer STA has
        		 * been deleted. And, these packets get assigned with a STA idx of
        		 * self-sta (since the peer STA has been deleted) and get transmitted
        		 * on the new channel before the reassoc request. Since there will be
        		 * no ACK on the new channel, each packet gets retransmitted which
        		 * takes several seconds before the transmission of reassoc request.
        		 * This leads to reassoc-timeout and roam failure.
    		     */
                status = hdd_roamDeregisterSTA( pAdapter, pHddStaCtx->conn_info.staId [0] );
                if ( !VOS_IS_STATUS_SUCCESS(status ) )
                {
                    VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_WARN,
                            FL("hdd_roamDeregisterSTA() failed to for staID %d.  Status= %d [0x%x]"),
                            pHddStaCtx->conn_info.staId[0], status, status );
                    halStatus = eHAL_STATUS_FAILURE;
                }		
            }
            pHddStaCtx->ft_carrier_on = TRUE;
            break;
#endif

        case eCSR_ROAM_SHOULD_ROAM:
           // Dont need to do anything
            {
                struct net_device *dev = pAdapter->dev;
                hdd_station_ctx_t *pHddStaCtx = WLAN_HDD_GET_STATION_CTX_PTR(pAdapter);
                // notify apps that we can't pass traffic anymore
                netif_tx_disable(dev);
#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_CCX) || defined(FEATURE_WLAN_LFR)
                if (pHddStaCtx->ft_carrier_on == FALSE)
                {
#endif
                    netif_carrier_off(dev);
#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_CCX) || defined(FEATURE_WLAN_LFR)
                }
#endif

#if  !(defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_CCX) || defined(FEATURE_WLAN_LFR))
                //We should clear all sta register with TL, for now, only one.
                status = hdd_roamDeregisterSTA( pAdapter, pHddStaCtx->conn_info.staId [0] );
                if ( !VOS_IS_STATUS_SUCCESS(status ) )
                {
                    VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_WARN,
                        FL("hdd_roamDeregisterSTA() failed to for staID %d.  Status= %d [0x%x]"),
                                        pHddStaCtx->conn_info.staId[0], status, status );
                    halStatus = eHAL_STATUS_FAILURE;
                }
#endif
                // Clear saved connection information in HDD
                hdd_connRemoveConnectInfo( WLAN_HDD_GET_STATION_CTX_PTR(pAdapter) );
            }
           break;
        case eCSR_ROAM_LOSTLINK:
        case eCSR_ROAM_DISASSOCIATED:
            {
                hdd_context_t* pHddCtx = (hdd_context_t*)pAdapter->pHddCtx;
                VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,
                        "****eCSR_ROAM_DISASSOCIATED****");
                halStatus = hdd_DisConnectHandler( pAdapter, pRoamInfo, roamId, roamStatus, roamResult );
                /* Check if Mcast/Bcast Filters are set, if yes clear the filters here */
                if ((WLAN_HDD_GET_CTX(pAdapter))->hdd_mcastbcast_filter_set == TRUE) {
                    hdd_conf_mcastbcast_filter((WLAN_HDD_GET_CTX(pAdapter)), FALSE);
                    (WLAN_HDD_GET_CTX(pAdapter))->hdd_mcastbcast_filter_set = FALSE;
                }
#ifdef WLAN_FEATURE_PACKET_FILTERING    
                if (pHddCtx->cfg_ini->isMcAddrListFilter)
                {
                    /*Multicast addr filtering is enabled*/
                    if(pHddCtx->mc_addr_list.isFilterApplied)
                    {
                        /*Filter applied during suspend mode*/
                        /*Clear it here*/
                        wlan_hdd_set_mc_addr_list(pHddCtx, FALSE, pAdapter->sessionId);
                    }
                }
#endif

                if (WLAN_HDD_P2P_CLIENT != pAdapter->device_mode)
                {
                    /* Disconnected from current AP. Reset the country code information
                     * so that it re-initialize the valid channel list*/
                    hdd_ResetCountryCodeAfterDisAssoc(pAdapter);
                }
            }
            break;
        case eCSR_ROAM_IBSS_LEAVE:
            VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,
                    "****eCSR_ROAM_IBSS_LEAVE****");
            halStatus = hdd_DisConnectHandler( pAdapter, pRoamInfo, roamId, roamStatus, roamResult );
            break;
        case eCSR_ROAM_ASSOCIATION_COMPLETION:
            VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO,
                    "****eCSR_ROAM_ASSOCIATION_COMPLETION****");
            if (  (roamResult != eCSR_ROAM_RESULT_ASSOCIATED)
               && (   (pWextState->roamProfile.EncryptionType.encryptionType[0] == eCSR_ENCRYPT_TYPE_WEP40_STATICKEY) 
                   || (pWextState->roamProfile.EncryptionType.encryptionType[0] == eCSR_ENCRYPT_TYPE_WEP104_STATICKEY)
                  )
               && (eCSR_AUTH_TYPE_SHARED_KEY != pWextState->roamProfile.AuthType.authType[0])
               )
            {
                v_U32_t roamId = 0;
                VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_INFO_HIGH,
                        "****WEP open authentication failed, trying with shared authentication****");
                (WLAN_HDD_GET_STATION_CTX_PTR(pAdapter))->conn_info.authType = eCSR_AUTH_TYPE_SHARED_KEY;
                pWextState->roamProfile.AuthType.authType[0] = (WLAN_HDD_GET_STATION_CTX_PTR(pAdapter))->conn_info.authType;
                pWextState->roamProfile.csrPersona = pAdapter->device_mode;
                halStatus = sme_RoamConnect( WLAN_HDD_GET_HAL_CTX(pAdapter), pAdapter->sessionId, &(pWextState->roamProfile), &roamId);
            }
            else
            {
                halStatus = hdd_AssociationCompletionHandler( pAdapter, pRoamInfo, roamId, roamStatus, roamResult );
            }

            break;
        case eCSR_ROAM_ASSOCIATION_FAILURE:
            halStatus = hdd_AssociationCompletionHandler( pAdapter, 
                    pRoamInfo, roamId, roamStatus, roamResult );
            break;
        case eCSR_ROAM_IBSS_IND:
            halStatus = roamRoamIbssIndicationHandler( pAdapter, pRoamInfo, roamId, roamStatus, roamResult );
            break;

        case eCSR_ROAM_CONNECT_STATUS_UPDATE:
            halStatus = roamRoamConnectStatusUpdateHandler( pAdapter, pRoamInfo, roamId, roamStatus, roamResult );
            break;            

        case eCSR_ROAM_MIC_ERROR_IND:
            halStatus = hdd_RoamMicErrorIndicationHandler( pAdapter, pRoamInfo, roamId, roamStatus, roamResult );
            break;

        case eCSR_ROAM_SET_KEY_COMPLETE:
            halStatus = hdd_RoamSetKeyCompleteHandler( pAdapter, pRoamInfo, roamId, roamStatus, roamResult );
            break;
#ifdef WLAN_FEATURE_VOWIFI_11R
        case eCSR_ROAM_FT_RESPONSE:
            hdd_SendFTEvent(pAdapter);
            break;
#endif
#ifdef FEATURE_WLAN_LFR
        case eCSR_ROAM_PMK_NOTIFY:
           if (eCSR_AUTH_TYPE_RSN == pHddStaCtx->conn_info.authType) 
           {
               /* Notify the supplicant of a new candidate */
               halStatus = wlan_hdd_cfg80211_pmksa_candidate_notify(pAdapter, pRoamInfo, 1, false);
           }
           break;
#endif

#ifdef WLAN_FEATURE_P2P
        case eCSR_ROAM_INDICATE_MGMT_FRAME:
            hdd_indicateMgmtFrame( pAdapter,
                                  pRoamInfo->nFrameLength,
                                  pRoamInfo->pbFrames,
                                  pRoamInfo->frameType,
                                  pRoamInfo->rxChan );
            break;
        case eCSR_ROAM_REMAIN_CHAN_READY:
            hdd_remainChanReadyHandler( pAdapter );
            break;
        case eCSR_ROAM_SEND_ACTION_CNF:
            hdd_sendActionCnf( pAdapter,
               (roamResult == eCSR_ROAM_RESULT_NONE) ? TRUE : FALSE );
            break;
#endif
        default:
            break;
    }
