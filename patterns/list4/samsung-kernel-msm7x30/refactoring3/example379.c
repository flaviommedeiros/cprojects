switch(sapEvent)
    {
        case eSAP_START_BSS_EVENT :
            hddLog(LOG1, FL("BSS configured status = %s, channel = %lu, bc sta Id = %d\n"),
                            pSapEvent->sapevt.sapStartBssCompleteEvent.status ? "eSAP_STATUS_FAILURE" : "eSAP_STATUS_SUCCESS",
                            pSapEvent->sapevt.sapStartBssCompleteEvent.operatingChannel,
                              pSapEvent->sapevt.sapStartBssCompleteEvent.staId);

            pHostapdState->vosStatus = pSapEvent->sapevt.sapStartBssCompleteEvent.status;
            vos_status = vos_event_set(&pHostapdState->vosEvent);
   
            if (!VOS_IS_STATUS_SUCCESS(vos_status) || pHostapdState->vosStatus)
            {     
                VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_ERROR, ("ERROR: startbss event failed!!\n"));
                goto stopbss;
            }
            else
            {                
                pHddApCtx->uBCStaId = pSapEvent->sapevt.sapStartBssCompleteEvent.staId;
                //@@@ need wep logic here to set privacy bit
                hdd_softap_Register_BC_STA(pHostapdAdapter, pHddApCtx->uPrivacy);
            }
            
            if (0 != (WLAN_HDD_GET_CTX(pHostapdAdapter))->cfg_ini->nAPAutoShutOff)
            {
                // AP Inactivity timer init and start
                vos_status = vos_timer_init( &pHddApCtx->hdd_ap_inactivity_timer, VOS_TIMER_TYPE_SW, 
                                            hdd_hostapd_inactivity_timer_cb, (v_PVOID_t)dev );
                if (!VOS_IS_STATUS_SUCCESS(vos_status))
                   hddLog(LOGE, FL("Failed to init AP inactivity timer\n"));

                vos_status = vos_timer_start( &pHddApCtx->hdd_ap_inactivity_timer, (WLAN_HDD_GET_CTX(pHostapdAdapter))->cfg_ini->nAPAutoShutOff * 1000);
                if (!VOS_IS_STATUS_SUCCESS(vos_status))
                   hddLog(LOGE, FL("Failed to init AP inactivity timer\n"));

            }
            pHddApCtx->operatingChannel = pSapEvent->sapevt.sapStartBssCompleteEvent.operatingChannel;
            pHostapdState->bssState = BSS_START;

            // Send current operating channel of SoftAP to BTC-ES
            send_btc_nlink_msg(WLAN_BTC_SOFTAP_BSS_START, 0);

#ifdef CONFIG_CFG80211            
            //Check if there is any group key pending to set.
            if( pHddApCtx->groupKey.keyLength )
            {
                 if( VOS_STATUS_SUCCESS !=  WLANSAP_SetKeySta( 
                               (WLAN_HDD_GET_CTX(pHostapdAdapter))->pvosContext,
                               &pHddApCtx->groupKey ) )
                 {
                      VOS_TRACE( VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_ERROR, 
                             "%s: WLANSAP_SetKeySta failed", __func__);
                 }
                 pHddApCtx->groupKey.keyLength = 0;
            }
            else if ( pHddApCtx->wepKey[0].keyLength )
            {
                int i=0;
                for ( i = 0; i < CSR_MAX_NUM_KEY; i++ ) 
                {
                    if( VOS_STATUS_SUCCESS !=  WLANSAP_SetKeySta(
                                (WLAN_HDD_GET_CTX(pHostapdAdapter))->pvosContext,
                                &pHddApCtx->wepKey[i] ) )
                    {   
                          VOS_TRACE( VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_ERROR,
                             "%s: WLANSAP_SetKeySta failed idx %d", __func__, i);
                    }
                    pHddApCtx->wepKey[i].keyLength = 0;
                }
           }
#endif
            //Fill the params for sending IWEVCUSTOM Event with SOFTAP.enabled
            startBssEvent = "SOFTAP.enabled";
            memset(&we_custom_start_event, '\0', sizeof(we_custom_start_event));
            memcpy(&we_custom_start_event, startBssEvent, strlen(startBssEvent));
            memset(&wrqu, 0, sizeof(wrqu));
            wrqu.data.length = strlen(startBssEvent);
            we_event = IWEVCUSTOM;
            we_custom_event_generic = we_custom_start_event;

            break; //Event will be sent after Switch-Case stmt 

        case eSAP_STOP_BSS_EVENT:
            hddLog(LOG1, FL("BSS stop status = %s\n"),pSapEvent->sapevt.sapStopBssCompleteEvent.status ? 
                             "eSAP_STATUS_FAILURE" : "eSAP_STATUS_SUCCESS");

            pHddApCtx->operatingChannel = 0; //Invalidate the channel info.
            vos_event_set(&pHostapdState->vosEvent);
            goto stopbss;
        case eSAP_STA_SET_KEY_EVENT:
            //TODO: forward the message to hostapd once implementtation is done for now just print
            hddLog(LOG1, FL("SET Key: configured status = %s\n"),pSapEvent->sapevt.sapStationSetKeyCompleteEvent.status ? 
                            "eSAP_STATUS_FAILURE" : "eSAP_STATUS_SUCCESS");
            return VOS_STATUS_SUCCESS;
        case eSAP_STA_DEL_KEY_EVENT:
           //TODO: forward the message to hostapd once implementtation is done for now just print
           hddLog(LOG1, FL("Event received %s\n"),"eSAP_STA_DEL_KEY_EVENT");
           return VOS_STATUS_SUCCESS;
        case eSAP_STA_MIC_FAILURE_EVENT:
        {
            struct iw_michaelmicfailure msg;
            memset(&msg, '\0', sizeof(msg));
            msg.src_addr.sa_family = ARPHRD_ETHER;
            memcpy(msg.src_addr.sa_data, &pSapEvent->sapevt.sapStationMICFailureEvent.staMac, sizeof(msg.src_addr.sa_data));
            hddLog(LOG1, "MIC MAC "MAC_ADDRESS_STR"\n", MAC_ADDR_ARRAY(msg.src_addr.sa_data));
            if(pSapEvent->sapevt.sapStationMICFailureEvent.multicast == eSAP_TRUE)
             msg.flags = IW_MICFAILURE_GROUP;
            else 
             msg.flags = IW_MICFAILURE_PAIRWISE;
            memset(&wrqu, 0, sizeof(wrqu));
            wrqu.data.length = sizeof(msg);
            we_event = IWEVMICHAELMICFAILURE;
            we_custom_event_generic = (v_BYTE_t *)&msg;
        }
#ifdef CONFIG_CFG80211
      /* inform mic failure to nl80211 */
        cfg80211_michael_mic_failure(dev, 
                                     pSapEvent->sapevt.
                                     sapStationMICFailureEvent.staMac.bytes,
                                     ((pSapEvent->sapevt.sapStationMICFailureEvent.multicast == eSAP_TRUE) ? 
                                      NL80211_KEYTYPE_GROUP :
                                      NL80211_KEYTYPE_PAIRWISE),
                                     pSapEvent->sapevt.sapStationMICFailureEvent.keyId, 
                                     pSapEvent->sapevt.sapStationMICFailureEvent.TSC, 
                                     GFP_KERNEL);
#endif
            break;
        
        case eSAP_STA_ASSOC_EVENT:
        case eSAP_STA_REASSOC_EVENT:
            wrqu.addr.sa_family = ARPHRD_ETHER;
            memcpy(wrqu.addr.sa_data, &pSapEvent->sapevt.sapStationAssocReassocCompleteEvent.staMac, 
                sizeof(wrqu.addr.sa_data));
            hddLog(LOG1, " associated "MAC_ADDRESS_STR"\n", MAC_ADDR_ARRAY(wrqu.addr.sa_data));
            we_event = IWEVREGISTERED;
            
            WLANSAP_Get_WPS_State((WLAN_HDD_GET_CTX(pHostapdAdapter))->pvosContext, &bWPSState);
         
            if ( (eCSR_ENCRYPT_TYPE_NONE == pHddApCtx->ucEncryptType) ||
                 ( eCSR_ENCRYPT_TYPE_WEP40_STATICKEY == pHddApCtx->ucEncryptType ) || 
                 ( eCSR_ENCRYPT_TYPE_WEP104_STATICKEY == pHddApCtx->ucEncryptType ) )
            {
                bAuthRequired = FALSE;
            }

            if (bAuthRequired || bWPSState == eANI_BOOLEAN_TRUE )
            {
                hdd_softap_RegisterSTA( pHostapdAdapter,
                                       TRUE,
                                       pHddApCtx->uPrivacy,
                                       pSapEvent->sapevt.sapStationAssocReassocCompleteEvent.staId,
                                       0,
                                       0,
                                       (v_MACADDR_t *)wrqu.addr.sa_data,
                                       pSapEvent->sapevt.sapStationAssocReassocCompleteEvent.wmmEnabled);
            }
            else
            {
                hdd_softap_RegisterSTA( pHostapdAdapter,
                                       FALSE,
                                       pHddApCtx->uPrivacy,
                                       pSapEvent->sapevt.sapStationAssocReassocCompleteEvent.staId,
                                       0,
                                       0,
                                       (v_MACADDR_t *)wrqu.addr.sa_data,
                                       pSapEvent->sapevt.sapStationAssocReassocCompleteEvent.wmmEnabled);
            } 
            
            // Stop AP inactivity timer
            if (pHddApCtx->hdd_ap_inactivity_timer.state == VOS_TIMER_STATE_RUNNING)
            {
                vos_status = vos_timer_stop(&pHddApCtx->hdd_ap_inactivity_timer);
                if (!VOS_IS_STATUS_SUCCESS(vos_status))
                   hddLog(LOGE, FL("Failed to start AP inactivity timer\n"));
            }
#ifdef CONFIG_CFG80211
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38))
            {
                struct station_info staInfo;
                v_U16_t iesLen =  pSapEvent->sapevt.sapStationAssocReassocCompleteEvent.iesLen;

                memset(&staInfo, 0, sizeof(staInfo));
                if (iesLen <= MAX_ASSOC_IND_IE_LEN )
                {
                    staInfo.assoc_req_ies =
                        (const u8 *)&pSapEvent->sapevt.sapStationAssocReassocCompleteEvent.ies[0];
                    staInfo.assoc_req_ies_len = iesLen;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0))
                    staInfo.filled |= STATION_INFO_ASSOC_REQ_IES;
#endif
                    cfg80211_new_sta(dev,
                                 (const u8 *)&pSapEvent->sapevt.sapStationAssocReassocCompleteEvent.staMac.bytes[0],
                                 &staInfo, GFP_KERNEL);
                }
                else
                {
                    hddLog(LOGE, FL(" Assoc Ie length is too long \n"));
                }
             }
#endif
#endif

            break;
        case eSAP_STA_DISASSOC_EVENT:
            memcpy(wrqu.addr.sa_data, &pSapEvent->sapevt.sapStationDisassocCompleteEvent.staMac,
                   sizeof(wrqu.addr.sa_data));
            hddLog(LOG1, " disassociated "MAC_ADDRESS_STR"\n", MAC_ADDR_ARRAY(wrqu.addr.sa_data));
            if (pSapEvent->sapevt.sapStationDisassocCompleteEvent.reason == eSAP_USR_INITATED_DISASSOC)
                hddLog(LOG1," User initiated disassociation");
            else
                hddLog(LOG1," MAC initiated disassociation");
            we_event = IWEVEXPIRED;
            vos_status = hdd_softap_GetStaId(pHostapdAdapter, &pSapEvent->sapevt.sapStationDisassocCompleteEvent.staMac, &staId);
            if (!VOS_IS_STATUS_SUCCESS(vos_status))
            {
                VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_ERROR, FL("ERROR: HDD Failed to find sta id!!"));
                return VOS_STATUS_E_FAILURE;
            }
            hdd_softap_DeregisterSTA(pHostapdAdapter, staId);

            if (0 != (WLAN_HDD_GET_CTX(pHostapdAdapter))->cfg_ini->nAPAutoShutOff)
            {
                spin_lock_bh( &pHostapdAdapter->staInfo_lock );
                // Start AP inactivity timer if no stations associated with it
                for (i = 0; i < WLAN_MAX_STA_COUNT; i++)
                {
                    if (pHostapdAdapter->aStaInfo[i].isUsed && i != (WLAN_HDD_GET_AP_CTX_PTR(pHostapdAdapter))->uBCStaId)
                    {
                        bApActive = TRUE;
                        break;
                    }
                }
                spin_unlock_bh( &pHostapdAdapter->staInfo_lock );

                if (bApActive == FALSE)
                {
                    if (pHddApCtx->hdd_ap_inactivity_timer.state == VOS_TIMER_STATE_STOPPED)
                    {
                        vos_status = vos_timer_start(&pHddApCtx->hdd_ap_inactivity_timer, (WLAN_HDD_GET_CTX(pHostapdAdapter))->cfg_ini->nAPAutoShutOff * 1000);
                        if (!VOS_IS_STATUS_SUCCESS(vos_status))
                            hddLog(LOGE, FL("Failed to init AP inactivity timer\n"));
                    }
                    else
                        VOS_ASSERT(vos_timer_getCurrentState(&pHddApCtx->hdd_ap_inactivity_timer) == VOS_TIMER_STATE_STOPPED);
                }
            }
#ifdef CONFIG_CFG80211
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38))
            cfg80211_del_sta(dev,
                            (const u8 *)&pSapEvent->sapevt.sapStationDisassocCompleteEvent.staMac.bytes[0],
                            GFP_KERNEL);
#endif
#endif
            break;
        case eSAP_WPS_PBC_PROBE_REQ_EVENT:
        {
                static const char * message ="MLMEWPSPBCPROBEREQ.indication";
                union iwreq_data wreq;
               
                down(&pHddApCtx->semWpsPBCOverlapInd);
                pHddApCtx->WPSPBCProbeReq.probeReqIELen = pSapEvent->sapevt.sapPBCProbeReqEvent.WPSPBCProbeReq.probeReqIELen;
                
                vos_mem_copy(pHddApCtx->WPSPBCProbeReq.probeReqIE, pSapEvent->sapevt.sapPBCProbeReqEvent.WPSPBCProbeReq.probeReqIE, 
                    pHddApCtx->WPSPBCProbeReq.probeReqIELen);
                     
                vos_mem_copy(pHddApCtx->WPSPBCProbeReq.peerMacAddr, pSapEvent->sapevt.sapPBCProbeReqEvent.WPSPBCProbeReq.peerMacAddr, sizeof(v_MACADDR_t));
                hddLog(LOG1, "WPS PBC probe req "MAC_ADDRESS_STR"\n", MAC_ADDR_ARRAY(pHddApCtx->WPSPBCProbeReq.peerMacAddr));
                memset(&wreq, 0, sizeof(wreq));
                wreq.data.length = strlen(message); // This is length of message
                wireless_send_event(dev, IWEVCUSTOM, &wreq, (char *)message); 
                
                return VOS_STATUS_SUCCESS;
        }
        case eSAP_ASSOC_STA_CALLBACK_EVENT:
            pAssocStasArray = pSapEvent->sapevt.sapAssocStaListEvent.pAssocStas;
            if (pSapEvent->sapevt.sapAssocStaListEvent.noOfAssocSta != 0)
            {   // List of associated stations
                for (i = 0; i < pSapEvent->sapevt.sapAssocStaListEvent.noOfAssocSta; i++)
                {
                    hddLog(LOG1,"Associated Sta Num %d:assocId=%d, staId=%d, staMac="MAC_ADDRESS_STR,
                        i+1,
                        pAssocStasArray->assocId,
                        pAssocStasArray->staId,
                                    MAC_ADDR_ARRAY(pAssocStasArray->staMac.bytes));
                        pAssocStasArray++;             
            }
            }
            vos_mem_free(pSapEvent->sapevt.sapAssocStaListEvent.pAssocStas);// Release caller allocated memory here
            return VOS_STATUS_SUCCESS;
#ifdef WLAN_FEATURE_P2P
        case eSAP_INDICATE_MGMT_FRAME:
           hdd_indicateMgmtFrame( pHostapdAdapter, 
                                 pSapEvent->sapevt.sapManagementFrameInfo.nFrameLength,
                                 pSapEvent->sapevt.sapManagementFrameInfo.pbFrames,
                                 pSapEvent->sapevt.sapManagementFrameInfo.frameType, 
                                 pSapEvent->sapevt.sapManagementFrameInfo.rxChan);
           return VOS_STATUS_SUCCESS;
        case eSAP_REMAIN_CHAN_READY:
           hdd_remainChanReadyHandler( pHostapdAdapter );
           return VOS_STATUS_SUCCESS;
        case eSAP_SEND_ACTION_CNF:
           hdd_sendActionCnf( pHostapdAdapter, 
                              ( eSAP_STATUS_SUCCESS == 
                                pSapEvent->sapevt.sapActionCnf.actionSendSuccess ) ? 
                                TRUE : FALSE );
           return VOS_STATUS_SUCCESS;
#endif
        case eSAP_UNKNOWN_STA_JOIN:
            snprintf(unknownSTAEvent, IW_CUSTOM_MAX, "JOIN_UNKNOWN_STA-%02x:%02x:%02x:%02x:%02x:%02x",
                pSapEvent->sapevt.sapUnknownSTAJoin.macaddr.bytes[0],
                pSapEvent->sapevt.sapUnknownSTAJoin.macaddr.bytes[1],
                pSapEvent->sapevt.sapUnknownSTAJoin.macaddr.bytes[2],
                pSapEvent->sapevt.sapUnknownSTAJoin.macaddr.bytes[3],
                pSapEvent->sapevt.sapUnknownSTAJoin.macaddr.bytes[4],
                pSapEvent->sapevt.sapUnknownSTAJoin.macaddr.bytes[5]);
            we_event = IWEVCUSTOM; /* Discovered a new node (AP mode). */
            wrqu.data.pointer = unknownSTAEvent;
            wrqu.data.length = strlen(unknownSTAEvent);
            we_custom_event_generic = (v_BYTE_t *)unknownSTAEvent;
            hddLog(LOG1,"%s\n", unknownSTAEvent);
            break;

        case eSAP_MAX_ASSOC_EXCEEDED:
            snprintf(maxAssocExceededEvent, IW_CUSTOM_MAX, "Peer %02x:%02x:%02x:%02x:%02x:%02x denied"
                    " assoc due to Maximum Mobile Hotspot connections reached. Please disconnect"
                    " one or more devices to enable the new device connection",
                    pSapEvent->sapevt.sapMaxAssocExceeded.macaddr.bytes[0],
                    pSapEvent->sapevt.sapMaxAssocExceeded.macaddr.bytes[1],
                    pSapEvent->sapevt.sapMaxAssocExceeded.macaddr.bytes[2],
                    pSapEvent->sapevt.sapMaxAssocExceeded.macaddr.bytes[3],
                    pSapEvent->sapevt.sapMaxAssocExceeded.macaddr.bytes[4],
                    pSapEvent->sapevt.sapMaxAssocExceeded.macaddr.bytes[5]);
            we_event = IWEVCUSTOM; /* Discovered a new node (AP mode). */
            wrqu.data.pointer = maxAssocExceededEvent;
            wrqu.data.length = strlen(maxAssocExceededEvent);
            we_custom_event_generic = (v_BYTE_t *)maxAssocExceededEvent;
            hddLog(LOG1,"%s\n", maxAssocExceededEvent);
            break;
        case eSAP_STA_ASSOC_IND:
            return VOS_STATUS_SUCCESS;
        default:
            hddLog(LOG1,"SAP message is not handled\n");
            goto stopbss;
            return VOS_STATUS_SUCCESS;
    }
