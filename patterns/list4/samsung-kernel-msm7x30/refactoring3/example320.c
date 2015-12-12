switch( pSirMsg->messageType ) 
    {
        case eWNI_SME_ASSOC_IND:
            {
                tCsrRoamSession  *pSession;
                smsLog( pMac, LOG1, FL("ASSOCIATION Indication from SME\n"));
                pAssocInd = (tSirSmeAssocInd *)pSirMsg;
                status = csrRoamGetSessionIdFromBSSID( pMac, (tCsrBssid *)pAssocInd->bssId, &sessionId );
                if( HAL_STATUS_SUCCESS( status ) )
                {
                    pSession = CSR_GET_SESSION(pMac, sessionId);

                    if(!pSession)
                    {
                        smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                        return;
                    }

                pRoamInfo = &roamInfo;

                // Required for indicating the frames to upper layer
                pRoamInfo->assocReqLength = pAssocInd->assocReqLength;
                pRoamInfo->assocReqPtr = pAssocInd->assocReqPtr;

                pRoamInfo->beaconPtr = pAssocInd->beaconPtr;
                pRoamInfo->beaconLength = pAssocInd->beaconLength;                
                pRoamInfo->statusCode = eSIR_SME_SUCCESS; //send the status code as Success 
                pRoamInfo->u.pConnectedProfile = &pSession->connectedProfile;

                    pRoamInfo->staId = (tANI_U8)pAssocInd->staId;
                    pRoamInfo->rsnIELen = (tANI_U8)pAssocInd->rsnIE.length;
                    pRoamInfo->prsnIE = pAssocInd->rsnIE.rsnIEdata;
                
                pRoamInfo->addIELen = (tANI_U8)pAssocInd->addIE.length;
                pRoamInfo->paddIE =  pAssocInd->addIE.addIEdata;
                    palCopyMemory(pMac->hHdd, pRoamInfo->peerMac, pAssocInd->peerMacAddr, sizeof(tSirMacAddr));
                    palCopyMemory(pMac->hHdd, &pRoamInfo->bssid, pAssocInd->bssId, sizeof(tCsrBssid));
#ifdef WLAN_SOFTAP_FEATURE
                    pRoamInfo->wmmEnabledSta = pAssocInd->wmmEnabledSta;
                    if(CSR_IS_WDS_AP( pRoamInfo->u.pConnectedProfile))
#endif 
                        status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_WDS_IND, eCSR_ROAM_RESULT_WDS_ASSOCIATION_IND);//Sta
#ifdef WLAN_SOFTAP_FEATURE
                    if(CSR_IS_INFRA_AP(pRoamInfo->u.pConnectedProfile))
                    {
                        if( CSR_IS_ENC_TYPE_STATIC( pSession->pCurRoamProfile->negotiatedUCEncryptionType ))
                        {
                            csrRoamIssueSetContextReq( pMac, sessionId, pSession->pCurRoamProfile->negotiatedUCEncryptionType, 
                                    pSession->pConnectBssDesc,
                                    &(pRoamInfo->peerMac),
                                    FALSE, TRUE, eSIR_TX_RX, 0, 0, NULL, 0 ); // NO keys... these key parameters don't matter.
                            pRoamInfo->fAuthRequired = FALSE;
                        }
                        else
                        {
                            pRoamInfo->fAuthRequired = TRUE;
                        }
                        status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_INFRA_IND, eCSR_ROAM_RESULT_INFRA_ASSOCIATION_IND);
                        if (!HAL_STATUS_SUCCESS(status))
                            pRoamInfo->statusCode = eSIR_SME_ASSOC_REFUSED;// Refused due to Mac filtering 
                    }
#endif 
                    /* Send Association completion message to PE */
                    status = csrSendAssocCnfMsg( pMac, pAssocInd, status );//Sta
                    
                    /* send a message to CSR itself just to avoid the EAPOL frames going
                     * OTA before association response */
                    if(CSR_IS_WDS_AP( pRoamInfo->u.pConnectedProfile))
                {
                    status = csrSendAssocIndToUpperLayerCnfMsg(pMac, pAssocInd, status, sessionId);
                }
#ifdef WLAN_SOFTAP_FEATURE
                else if(CSR_IS_INFRA_AP(pRoamInfo->u.pConnectedProfile) && (pRoamInfo->statusCode != eSIR_SME_ASSOC_REFUSED))
                {
                    pRoamInfo->fReassocReq = pAssocInd->reassocReq;
                    //status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_INFRA_IND, eCSR_ROAM_RESULT_INFRA_ASSOCIATION_CNF);
                    status = csrSendAssocIndToUpperLayerCnfMsg(pMac, pAssocInd, status, sessionId);
                }
#endif
                }
            }
            break;
        case eWNI_SME_DISASSOC_IND:
            smsLog( pMac, LOGE, FL("DISASSOCIATION Indication from MAC\n"));
            // Check if AP dis-associated us because of MIC failure. If so,
            // then we need to take action immediately and not wait till the
            // the WmStatusChange requests is pushed and processed
            pDisassocInd = (tSirSmeDisassocInd *)pSirMsg;
            status = csrRoamGetSessionIdFromBSSID( pMac, (tCsrBssid *)pDisassocInd->bssId, &sessionId );
            if( HAL_STATUS_SUCCESS( status ) )
            {
                // If we are in neighbor preauth done state then on receiving
                // disassoc or deauth we dont roam instead we just disassoc
                // from current ap and then go to disconnected state 
                // This happens for CCX and 11r FT connections ONLY.
#ifdef WLAN_FEATURE_VOWIFI_11R
                if (csrRoamIs11rAssoc(pMac) && (csrNeighborRoamStatePreauthDone(pMac)))
                {
                    csrNeighborRoamTranistionPreauthDoneToDisconnected(pMac);
                }
#endif
#ifdef FEATURE_WLAN_CCX
                if (csrRoamIsCCXAssoc(pMac) && (csrNeighborRoamStatePreauthDone(pMac)))
                {
                    csrNeighborRoamTranistionPreauthDoneToDisconnected(pMac);
                }
#endif
#ifdef FEATURE_WLAN_LFR
                if (csrRoamIsFastRoamEnabled(pMac) && (csrNeighborRoamStatePreauthDone(pMac)))
                {
                    csrNeighborRoamTranistionPreauthDoneToDisconnected(pMac);
                }
#endif
                pSession = CSR_GET_SESSION( pMac, sessionId );

                if(!pSession)
                {
                    smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                    return;
                }

                if ( csrIsConnStateInfra( pMac, sessionId ) )
                {
                    pSession->connectState = eCSR_ASSOC_STATE_TYPE_NOT_CONNECTED;
                }
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
                sme_QosCsrEventInd(pMac, (v_U8_t)sessionId, SME_QOS_CSR_DISCONNECT_IND, NULL);
#endif
                csrRoamLinkDown(pMac, sessionId);
                csrRoamIssueWmStatusChange( pMac, sessionId, eCsrDisassociated, pSirMsg );
#ifdef WLAN_SOFTAP_FEATURE
                if(CSR_IS_INFRA_AP(&pSession->connectedProfile))
                {

                    pRoamInfo = &roamInfo;

                    pRoamInfo->statusCode = pDisassocInd->statusCode; 
                    pRoamInfo->u.pConnectedProfile = &pSession->connectedProfile;

                    pRoamInfo->staId = (tANI_U8)pDisassocInd->staId;

                    palCopyMemory(pMac->hHdd, pRoamInfo->peerMac, pDisassocInd->peerMacAddr, sizeof(tSirMacAddr));
                    palCopyMemory(pMac->hHdd, &pRoamInfo->bssid, pDisassocInd->bssId, sizeof(tCsrBssid));

                    status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_INFRA_IND, eCSR_ROAM_RESULT_DISASSOC_IND);
                }
#endif                
            }
            break;
        case eWNI_SME_DEAUTH_IND:
            smsLog( pMac, LOG1, FL("DEAUTHENTICATION Indication from MAC\n"));
            pDeauthInd = (tpSirSmeDeauthInd)pSirMsg;
            status = csrRoamGetSessionIdFromBSSID( pMac, (tCsrBssid *)pDeauthInd->bssId, &sessionId );
            if( HAL_STATUS_SUCCESS( status ) )
            {
                // If we are in neighbor preauth done state then on receiving
                // disassoc or deauth we dont roam instead we just disassoc
                // from current ap and then go to disconnected state 
                // This happens for CCX and 11r FT connections ONLY.
#ifdef WLAN_FEATURE_VOWIFI_11R
                if (csrRoamIs11rAssoc(pMac) && (csrNeighborRoamStatePreauthDone(pMac)))
                {
                    csrNeighborRoamTranistionPreauthDoneToDisconnected(pMac);
                }
#endif
#ifdef FEATURE_WLAN_CCX
                if (csrRoamIsCCXAssoc(pMac) && (csrNeighborRoamStatePreauthDone(pMac)))
                {
                    csrNeighborRoamTranistionPreauthDoneToDisconnected(pMac);
                }
#endif
#ifdef FEATURE_WLAN_LFR
                if (csrRoamIsFastRoamEnabled(pMac) && (csrNeighborRoamStatePreauthDone(pMac)))
                {
                    csrNeighborRoamTranistionPreauthDoneToDisconnected(pMac);
                }
#endif
                pSession = CSR_GET_SESSION( pMac, sessionId );

                if(!pSession)
                {
                    smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                    return;
                }

                if ( csrIsConnStateInfra( pMac, sessionId ) )
                {
                    pSession->connectState = eCSR_ASSOC_STATE_TYPE_NOT_CONNECTED;
                }
#ifndef WLAN_MDM_CODE_REDUCTION_OPT
                sme_QosCsrEventInd(pMac, (v_U8_t)sessionId, SME_QOS_CSR_DISCONNECT_IND, NULL);
#endif
                csrRoamLinkDown(pMac, sessionId);
                csrRoamIssueWmStatusChange( pMac, sessionId, eCsrDeauthenticated, pSirMsg );
#ifdef WLAN_SOFTAP_FEATURE
                if(CSR_IS_INFRA_AP(&pSession->connectedProfile))
                {

                    pRoamInfo = &roamInfo;

                    pRoamInfo->statusCode = pDeauthInd->statusCode;
                    pRoamInfo->u.pConnectedProfile = &pSession->connectedProfile;

                    pRoamInfo->staId = (tANI_U8)pDeauthInd->staId;

                    palCopyMemory(pMac->hHdd, pRoamInfo->peerMac, pDeauthInd->peerMacAddr, sizeof(tSirMacAddr));
                    palCopyMemory(pMac->hHdd, &pRoamInfo->bssid, pDeauthInd->bssId, sizeof(tCsrBssid));

                    status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_INFRA_IND, eCSR_ROAM_RESULT_DEAUTH_IND);
                }
#endif                
            }
            break;
        
        case eWNI_SME_SWITCH_CHL_REQ:        // in case of STA, the SWITCH_CHANNEL originates from its AP
            smsLog( pMac, LOGW, FL("eWNI_SME_SWITCH_CHL_REQ from SME\n"));
            pSwitchChnInd = (tpSirSmeSwitchChannelInd)pSirMsg;
            //Update with the new channel id.
            //The channel id is hidden in the statusCode.
            status = csrRoamGetSessionIdFromBSSID( pMac, (tCsrBssid *)pSwitchChnInd->bssId, &sessionId );
            if( HAL_STATUS_SUCCESS( status ) )
            {
                pSession = CSR_GET_SESSION( pMac, sessionId );
                if(!pSession)
                {
                    smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                    return;
                }
                pSession->connectedProfile.operationChannel = (tANI_U8)pSwitchChnInd->newChannelId;
                if(pSession->pConnectBssDesc)
                {
                    pSession->pConnectBssDesc->channelId = (tANI_U8)pSwitchChnInd->newChannelId;
                }
            }
            break;
                
        case eWNI_SME_DEAUTH_RSP:
            smsLog( pMac, LOGW, FL("eWNI_SME_DEAUTH_RSP from SME\n"));
#ifdef WLAN_SOFTAP_FEATURE
            {
                tSirSmeDeauthRsp* pDeauthRsp = (tSirSmeDeauthRsp *)pSirMsg;
                sessionId = pDeauthRsp->sessionId;
                if( CSR_IS_SESSION_VALID(pMac, sessionId) )
                {                    
                    pSession = CSR_GET_SESSION(pMac, sessionId);
                    if(!pSession)
                    {
                        smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                        return;
                    }
                    if ( CSR_IS_INFRA_AP(&pSession->connectedProfile) )
                    {
                        pRoamInfo = &roamInfo;
                        pRoamInfo->u.pConnectedProfile = &pSession->connectedProfile;
                        palCopyMemory(pMac->hHdd, pRoamInfo->peerMac, pDeauthRsp->peerMacAddr, sizeof(tSirMacAddr));
                        pRoamInfo->reasonCode = eCSR_ROAM_RESULT_FORCED;
                        pRoamInfo->statusCode = pDeauthRsp->statusCode;
                        status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_LOSTLINK, eCSR_ROAM_RESULT_FORCED);
                    }
                }
            }
#endif
            break;
            
        case eWNI_SME_DISASSOC_RSP:
            smsLog( pMac, LOGW, FL("eWNI_SME_DISASSOC_RSP from SME subState = %d\n"), pMac->roam.curSubState[sessionId]);
#ifdef WLAN_SOFTAP_FEATURE
            {
                tSirSmeDisassocRsp *pDisassocRsp = (tSirSmeDisassocRsp *)pSirMsg;
                sessionId = pDisassocRsp->sessionId;
                if( CSR_IS_SESSION_VALID(pMac, sessionId) )
                {                    
                    pSession = CSR_GET_SESSION(pMac, sessionId);
                    if(!pSession)
                    {
                        smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                        return;
                    }
                    if ( CSR_IS_INFRA_AP(&pSession->connectedProfile) )
                    {
                        pRoamInfo = &roamInfo;
                        pRoamInfo->u.pConnectedProfile = &pSession->connectedProfile;
                        palCopyMemory(pMac->hHdd, pRoamInfo->peerMac, pDisassocRsp->peerMacAddr, sizeof(tSirMacAddr));
                        pRoamInfo->reasonCode = eCSR_ROAM_RESULT_FORCED;
                        pRoamInfo->statusCode = pDisassocRsp->statusCode;
                        status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_LOSTLINK, eCSR_ROAM_RESULT_FORCED);
                    }
                }
            }
#endif
            break;
        case eWNI_SME_MIC_FAILURE_IND:
            {
                tpSirSmeMicFailureInd pMicInd = (tpSirSmeMicFailureInd)pSirMsg;
                tCsrRoamInfo roamInfo, *pRoamInfo = NULL;
                eCsrRoamResult result = eCSR_ROAM_RESULT_MIC_ERROR_UNICAST;
#ifdef FEATURE_WLAN_DIAG_SUPPORT_CSR
                {
                    tCsrRoamSession *pSession = CSR_GET_SESSION( pMac, sessionId );
                    if(!pSession)
                    {
                        smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                        return;
                    }
                    WLAN_VOS_DIAG_EVENT_DEF(secEvent, vos_event_wlan_security_payload_type);
                    palZeroMemory(pMac->hHdd, &secEvent, sizeof(vos_event_wlan_security_payload_type));
                    secEvent.eventId = WLAN_SECURITY_EVENT_MIC_ERROR;
                    secEvent.encryptionModeMulticast = 
                        (v_U8_t)diagEncTypeFromCSRType(pSession->connectedProfile.mcEncryptionType);
                    secEvent.encryptionModeUnicast = 
                        (v_U8_t)diagEncTypeFromCSRType(pSession->connectedProfile.EncryptionType);
                    secEvent.authMode = 
                        (v_U8_t)diagAuthTypeFromCSRType(pSession->connectedProfile.AuthType);
                    palCopyMemory( pMac->hHdd, secEvent.bssid, pSession->connectedProfile.bssid, 6 );
                    WLAN_VOS_DIAG_EVENT_REPORT(&secEvent, EVENT_WLAN_SECURITY);
                }
#endif//FEATURE_WLAN_DIAG_SUPPORT_CSR
                status = csrRoamGetSessionIdFromBSSID( pMac, (tCsrBssid *)pMicInd->bssId, &sessionId );
                if( HAL_STATUS_SUCCESS( status ) )
                {
                    palZeroMemory(pMac->hHdd, &roamInfo, sizeof(tCsrRoamInfo));
                    roamInfo.u.pMICFailureInfo = &pMicInd->info;
                    pRoamInfo = &roamInfo;
                    if(pMicInd->info.multicast)
                    {
                        result = eCSR_ROAM_RESULT_MIC_ERROR_GROUP;
                    }
                    else
                    {
                        result = eCSR_ROAM_RESULT_MIC_ERROR_UNICAST;
                    }
                    csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_MIC_ERROR_IND, result);
                }
            }
            break;
#ifdef WLAN_SOFTAP_FEATURE
        case eWNI_SME_WPS_PBC_PROBE_REQ_IND:
            {
                tpSirSmeProbeReqInd pProbeReqInd = (tpSirSmeProbeReqInd)pSirMsg;
                tCsrRoamInfo roamInfo;
                smsLog( pMac, LOG1, FL("WPS PBC Probe request Indication from SME\n"));
           
                status = csrRoamGetSessionIdFromBSSID( pMac, (tCsrBssid *)pProbeReqInd->bssId, &sessionId );
                if( HAL_STATUS_SUCCESS( status ) )
                {
                    palZeroMemory(pMac->hHdd, &roamInfo, sizeof(tCsrRoamInfo));
                    roamInfo.u.pWPSPBCProbeReq = &pProbeReqInd->WPSPBCProbeReq;
                    csrRoamCallCallback(pMac, sessionId, &roamInfo, 0, eCSR_ROAM_WPS_PBC_PROBE_REQ_IND, 
                        eCSR_ROAM_RESULT_WPS_PBC_PROBE_REQ_IND);
                }
            }
            break;        
#endif
            
        case eWNI_SME_WM_STATUS_CHANGE_NTF:
            pStatusChangeMsg = (tSirSmeWmStatusChangeNtf *)pSirMsg;
            switch( pStatusChangeMsg->statusChangeCode ) 
            {
                case eSIR_SME_IBSS_ACTIVE:
                    sessionId = csrFindIbssSession( pMac );
                    if( CSR_SESSION_ID_INVALID != sessionId )
                    {
                        pSession = CSR_GET_SESSION( pMac, sessionId );
                        if(!pSession)
                        {
                            smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                            return;
                        }
                        pSession->connectState = eCSR_ASSOC_STATE_TYPE_IBSS_CONNECTED;
                        if(pSession->pConnectBssDesc)
                        {
                            palCopyMemory(pMac->hHdd, &roamInfo.bssid, pSession->pConnectBssDesc->bssId, sizeof(tCsrBssid));
                            roamInfo.u.pConnectedProfile = &pSession->connectedProfile;
                            pRoamInfo = &roamInfo;
                        }
                        else
                        {
                            smsLog(pMac, LOGE, "  CSR eSIR_SME_IBSS_NEW_PEER connected BSS is empty\n");
                        }
                        result = eCSR_ROAM_RESULT_IBSS_CONNECT;
                        roamStatus = eCSR_ROAM_CONNECT_STATUS_UPDATE;
                    }
                    break;
                case eSIR_SME_IBSS_INACTIVE:
                    sessionId = csrFindIbssSession( pMac );
                    if( CSR_SESSION_ID_INVALID != sessionId )
                    {
                        pSession = CSR_GET_SESSION( pMac, sessionId );
                        if(!pSession)
                        {
                            smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                            return;
                        }
                        pSession->connectState = eCSR_ASSOC_STATE_TYPE_IBSS_DISCONNECTED;
                        result = eCSR_ROAM_RESULT_IBSS_INACTIVE;
                        roamStatus = eCSR_ROAM_CONNECT_STATUS_UPDATE;
                    }
                    break;
                case eSIR_SME_JOINED_NEW_BSS:    // IBSS coalescing.
                    sessionId = csrFindIbssSession( pMac );
                    if( CSR_SESSION_ID_INVALID != sessionId )
                    {
                        pSession = CSR_GET_SESSION( pMac, sessionId );
                        if(!pSession)
                        {
                            smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                            return;
                        }
                        // update the connection state information
                        pNewBss = &pStatusChangeMsg->statusChangeInfo.newBssInfo;
#ifdef FEATURE_WLAN_DIAG_SUPPORT_CSR
                        {
                            vos_log_ibss_pkt_type *pIbssLog;
                            tANI_U32 bi;
                            WLAN_VOS_DIAG_LOG_ALLOC(pIbssLog, vos_log_ibss_pkt_type, LOG_WLAN_IBSS_C);
                            if(pIbssLog)
                            {
                                pIbssLog->eventId = WLAN_IBSS_EVENT_COALESCING;
                                if(pNewBss)
                                {
                                    palCopyMemory(pMac->hHdd, pIbssLog->bssid, pNewBss->bssId, 6);
                                    if(pNewBss->ssId.length)
                                    {
                                        palCopyMemory(pMac->hHdd, pIbssLog->ssid, pNewBss->ssId.ssId, pNewBss->ssId.length);
                                    }
                                    pIbssLog->operatingChannel = pNewBss->channelNumber;
                                }
                                if(HAL_STATUS_SUCCESS(ccmCfgGetInt(pMac, WNI_CFG_BEACON_INTERVAL, &bi)))
                                {
                                    //***U8 is not enough for beacon interval
                                    pIbssLog->beaconInterval = (v_U8_t)bi;
                                }
                                WLAN_VOS_DIAG_LOG_REPORT(pIbssLog);
                            }
                        }
#endif //FEATURE_WLAN_DIAG_SUPPORT_CSR
                        csrRoamUpdateConnectedProfileFromNewBss( pMac, sessionId, pNewBss );
                        csrRoamIssueSetContextReq( pMac, sessionId, pSession->connectedProfile.EncryptionType, 
                                                    pSession->pConnectBssDesc,
                                                &Broadcastaddr,
                                                FALSE, FALSE, eSIR_TX_RX, 0, 0, NULL, 0 );
                        result = eCSR_ROAM_RESULT_IBSS_COALESCED;
                        roamStatus = eCSR_ROAM_IBSS_IND;
                        palCopyMemory(pMac->hHdd, &roamInfo.bssid, &pNewBss->bssId, sizeof(tCsrBssid));
                        pRoamInfo = &roamInfo;
                        //This BSSID is th ereal BSSID, let's save it
                        if(pSession->pConnectBssDesc)
                        {
                            palCopyMemory(pMac->hHdd, pSession->pConnectBssDesc->bssId, &pNewBss->bssId, sizeof(tCsrBssid));
                        }
                        // Stop the join IBSS timer in case of join, for 
                        // genuine merge do nothing
                        if(pSession->ibss_join_pending)
                        {
                           pSession->ibss_join_pending = FALSE;
                           csrRoamStopIbssJoinTimer(pMac, sessionId);
                           result = eCSR_ROAM_RESULT_IBSS_JOIN_SUCCESS;
                        }
                    }
                    smsLog(pMac, LOGW, "CSR:  eSIR_SME_JOINED_NEW_BSS received from PE\n");
                    break;
                // detection by LIM that the capabilities of the associated AP have changed.
                case eSIR_SME_AP_CAPS_CHANGED:
                    pApNewCaps = &pStatusChangeMsg->statusChangeInfo.apNewCaps;
                    smsLog(pMac, LOGW, "CSR handling eSIR_SME_AP_CAPS_CHANGED\n");
                    status = csrRoamGetSessionIdFromBSSID( pMac, (tCsrBssid *)pApNewCaps->bssId, &sessionId );
                    if( HAL_STATUS_SUCCESS( status ) )
                    {
                    csrScanForCapabilityChange( pMac, pApNewCaps );
                    result = eCSR_ROAM_RESULT_CAP_CHANGED;
                    roamStatus = eCSR_ROAM_GEN_INFO;
                    }
                    break;
            
                default:
                    roamStatus = eCSR_ROAM_FAILED;
                    result = eCSR_ROAM_RESULT_NONE;
                    break;
            }  // end switch on statusChangeCode
            if(eCSR_ROAM_RESULT_NONE != result)
            {
                csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, roamStatus, result);
            }
            break;
        case eWNI_SME_IBSS_NEW_PEER_IND:
            pIbssPeerInd = (tSmeIbssPeerInd *)pSirMsg;
#ifdef FEATURE_WLAN_DIAG_SUPPORT_CSR
            {
                vos_log_ibss_pkt_type *pIbssLog;
                WLAN_VOS_DIAG_LOG_ALLOC(pIbssLog, vos_log_ibss_pkt_type, LOG_WLAN_IBSS_C);
                if(pIbssLog)
                {
                    pIbssLog->eventId = WLAN_IBSS_EVENT_PEER_JOIN;
                    palCopyMemory(pMac->hHdd, pIbssLog->peerMacAddr, &pIbssPeerInd->peerAddr, 6);
                    WLAN_VOS_DIAG_LOG_REPORT(pIbssLog);
                }
            }
#endif //FEATURE_WLAN_DIAG_SUPPORT_CSR
            sessionId = csrFindIbssSession( pMac );
            if( CSR_SESSION_ID_INVALID != sessionId )
            {
                pSession = CSR_GET_SESSION( pMac, sessionId );

                if(!pSession)
                {
                    smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                    return;
                }
            // Issue the set Context request to LIM to establish the Unicast STA context for the new peer...
                if(pSession->pConnectBssDesc)
                {
                    palCopyMemory(pMac->hHdd, &roamInfo.peerMac, pIbssPeerInd->peerAddr, sizeof(tCsrBssid));
                    palCopyMemory(pMac->hHdd, &roamInfo.bssid, pSession->pConnectBssDesc->bssId, sizeof(tCsrBssid));
                    if(pIbssPeerInd->mesgLen > sizeof(tSmeIbssPeerInd))
                    {
                        status = palAllocateMemory(pMac->hHdd, (void **)&roamInfo.pbFrames, 
                                                (pIbssPeerInd->mesgLen - sizeof(tSmeIbssPeerInd)));
                        if(HAL_STATUS_SUCCESS(status))
                        {
                            roamInfo.nBeaconLength = (pIbssPeerInd->mesgLen - sizeof(tSmeIbssPeerInd));
                            palCopyMemory(pMac->hHdd, roamInfo.pbFrames, ((tANI_U8 *)pIbssPeerInd) + sizeof(tSmeIbssPeerInd),
                                                roamInfo.nBeaconLength);
                        }
                        roamInfo.staId = (tANI_U8)pIbssPeerInd->staId;
                        roamInfo.ucastSig = (tANI_U8)pIbssPeerInd->ucastSig;
                        roamInfo.bcastSig = (tANI_U8)pIbssPeerInd->bcastSig;
                        status = palAllocateMemory(pMac->hHdd, (void **)&roamInfo.pBssDesc, 
                                                pSession->pConnectBssDesc->length);
                        if(HAL_STATUS_SUCCESS(status))
                        {
                            palCopyMemory(pMac->hHdd, roamInfo.pBssDesc, pSession->pConnectBssDesc, 
                                                pSession->pConnectBssDesc->length);
                        }
                        if(HAL_STATUS_SUCCESS(status))
                        {
                            pRoamInfo = &roamInfo;
                        }
                        else
                        {
                            if(roamInfo.pbFrames)
                            {
                                palFreeMemory(pMac->hHdd, roamInfo.pbFrames);
                            }
                            if(roamInfo.pBssDesc)
                            {
                                palFreeMemory(pMac->hHdd, roamInfo.pBssDesc);
                            }
                        }
                    }
                    else
                    {
                        pRoamInfo = &roamInfo;
                    }
                        csrRoamIssueSetContextReq( pMac, sessionId, pSession->connectedProfile.EncryptionType, 
                                            pSession->pConnectBssDesc,
                                            &(pIbssPeerInd->peerAddr),
                                            FALSE, TRUE, eSIR_TX_RX, 0, 0, NULL, 0 ); // NO keys... these key parameters don't matter.
                }
                else
                {
                    smsLog(pMac, LOGW, "  CSR eSIR_SME_IBSS_NEW_PEER connected BSS is empty\n");
                }
                //send up the sec type for the new peer
                if (pRoamInfo)
                {
                    pRoamInfo->u.pConnectedProfile = &pSession->connectedProfile;
                }
                csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, 
                            eCSR_ROAM_CONNECT_STATUS_UPDATE, eCSR_ROAM_RESULT_IBSS_NEW_PEER);
                if(pRoamInfo)
                {
                    if(roamInfo.pbFrames)
                    {
                        palFreeMemory(pMac->hHdd, roamInfo.pbFrames);
                    }
                    if(roamInfo.pBssDesc)
                    {
                        palFreeMemory(pMac->hHdd, roamInfo.pBssDesc);
                    }
                }
            }
            break;
        case eWNI_SME_IBSS_PEER_DEPARTED_IND:
            pIbssPeerInd = (tSmeIbssPeerInd*)pSirMsg;
            sessionId = csrFindIbssSession( pMac );
            if( CSR_SESSION_ID_INVALID != sessionId )
            {
#ifdef FEATURE_WLAN_DIAG_SUPPORT_CSR
                {
                    vos_log_ibss_pkt_type *pIbssLog;
 
                    WLAN_VOS_DIAG_LOG_ALLOC(pIbssLog, vos_log_ibss_pkt_type, LOG_WLAN_IBSS_C);
                    if(pIbssLog)
                    {
                        pIbssLog->eventId = WLAN_IBSS_EVENT_PEER_LEAVE;
                        if(pIbssPeerInd)
                        {
                            palCopyMemory(pMac->hHdd, pIbssLog->peerMacAddr, &pIbssPeerInd->peerAddr, 6);
                        }
                        WLAN_VOS_DIAG_LOG_REPORT(pIbssLog);
                    }
                }
#endif //FEATURE_WLAN_DIAG_SUPPORT_CSR
                smsLog(pMac, LOGW, "CSR: Peer departed notification from LIM\n");
                roamInfo.staId = (tANI_U8)pIbssPeerInd->staId;
                roamInfo.ucastSig = (tANI_U8)pIbssPeerInd->ucastSig;
                roamInfo.bcastSig = (tANI_U8)pIbssPeerInd->bcastSig;
                palCopyMemory(pMac->hHdd, &roamInfo.peerMac, pIbssPeerInd->peerAddr, sizeof(tCsrBssid));
                csrRoamCallCallback(pMac, sessionId, &roamInfo, 0, 
                        eCSR_ROAM_CONNECT_STATUS_UPDATE, eCSR_ROAM_RESULT_IBSS_PEER_DEPARTED);
            }
            break;
        case eWNI_SME_SETCONTEXT_RSP:
            {
                tSirSmeSetContextRsp *pRsp = (tSirSmeSetContextRsp *)pSirMsg;
                tListElem *pEntry;
                tSmeCmd *pCommand;
                
                pEntry = csrLLPeekHead( &pMac->sme.smeCmdActiveList, LL_ACCESS_LOCK );
                if ( pEntry )
                {
                    pCommand = GET_BASE_ADDR( pEntry, tSmeCmd, Link );
                    if ( eSmeCommandSetKey == pCommand->command )
                    {                
                        sessionId = pCommand->sessionId;        
                        pSession = CSR_GET_SESSION( pMac, sessionId );

                        if(!pSession)
                        {
                            smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                            return;
                        }
       
#ifdef FEATURE_WLAN_DIAG_SUPPORT_CSR
                        if(eCSR_ENCRYPT_TYPE_NONE != pSession->connectedProfile.EncryptionType)
                        {
                            WLAN_VOS_DIAG_EVENT_DEF(setKeyEvent, vos_event_wlan_security_payload_type);
                            palZeroMemory(pMac->hHdd, &setKeyEvent, sizeof(vos_event_wlan_security_payload_type));
                            if( pRsp->peerMacAddr[0] & 0x01 )
                            {
                                setKeyEvent.eventId = WLAN_SECURITY_EVENT_SET_GTK_RSP;
                            }
                            else
                            {
                                setKeyEvent.eventId = WLAN_SECURITY_EVENT_SET_PTK_RSP;
                            }
                            setKeyEvent.encryptionModeMulticast = 
                                (v_U8_t)diagEncTypeFromCSRType(pSession->connectedProfile.mcEncryptionType);
                            setKeyEvent.encryptionModeUnicast = 
                                (v_U8_t)diagEncTypeFromCSRType(pSession->connectedProfile.EncryptionType);
                            palCopyMemory( pMac->hHdd, setKeyEvent.bssid, pSession->connectedProfile.bssid, 6 );
                            setKeyEvent.authMode = 
                                (v_U8_t)diagAuthTypeFromCSRType(pSession->connectedProfile.AuthType);
                            if( eSIR_SUCCESS != pRsp->statusCode )
                            {
                                setKeyEvent.status = WLAN_SECURITY_STATUS_FAILURE;
                            }
                            WLAN_VOS_DIAG_EVENT_REPORT(&setKeyEvent, EVENT_WLAN_SECURITY);
                        }
#endif //FEATURE_WLAN_DIAG_SUPPORT_CSR
                        if( CSR_IS_WAIT_FOR_KEY( pMac, sessionId) )
                        {
                            //We are done with authentication, whethere succeed or not
                            csrRoamSubstateChange( pMac, eCSR_ROAM_SUBSTATE_NONE, sessionId);

                            csrRoamStopWaitForKeyTimer( pMac );
                            //We do it here because this linkup function is not called after association 
                            //when a key needs to be set. 
                            if( csrIsConnStateConnectedInfra(pMac, sessionId) ) 
                            {
                                csrRoamLinkUp(pMac, pSession->connectedProfile.bssid);
                            }
                        }
                        if( eSIR_SME_SUCCESS == pRsp->statusCode )
                        {
                            palCopyMemory( pMac, &roamInfo.peerMac, &pRsp->peerMacAddr, sizeof(tCsrBssid) );
                                //Make sure we install the GTK before indicating to HDD as authenticated
                                //This is to prevent broadcast packets go out after PTK and before GTK.
                                if( palEqualMemory( pMac->hHdd, &Broadcastaddr, pRsp->peerMacAddr, 
                                           sizeof(tSirMacAddr) ) )
                                {
                                    result = eCSR_ROAM_RESULT_AUTHENTICATED;
                                }
                                else
                                {
                                    result = eCSR_ROAM_RESULT_NONE;
                                }
                            pRoamInfo = &roamInfo;
                        }
                        else
                        {
                            result = eCSR_ROAM_RESULT_FAILURE;
                            smsLog( pMac, LOGE, "CSR: Roam Completion setkey command failed(%d) PeerMac %02X-%02X-%02X-%02X-%02X-%02X...\n", 
                                pRsp->statusCode, pRsp->peerMacAddr[0], pRsp->peerMacAddr[1], pRsp->peerMacAddr[2],
                                pRsp->peerMacAddr[3], pRsp->peerMacAddr[4], pRsp->peerMacAddr[5] );
                        }
                        csrRoamCallCallback(pMac, sessionId, &roamInfo, pCommand->u.setKeyCmd.roamId, 
                                            eCSR_ROAM_SET_KEY_COMPLETE, result);
                        // Indicate SME_QOS that the SET_KEY is completed, so that SME_QOS
                        // can go ahead and initiate the TSPEC if any are pending
                        sme_QosCsrEventInd(pMac, (v_U8_t)sessionId, SME_QOS_CSR_SET_KEY_SUCCESS_IND, NULL);
#ifdef FEATURE_WLAN_CCX
                        //Send Adjacent AP repot to new AP.
                        if (result == eCSR_ROAM_RESULT_AUTHENTICATED &&
                            pSession->isPrevApInfoValid && 
                            pSession->connectedProfile.isCCXAssoc)
                        {
#ifdef WLAN_FEATURE_VOWIFI
                            csrCcxSendAdjacentApRepMsg(pMac, pSession);
#endif
                            pSession->isPrevApInfoValid = FALSE;
                        }
#endif
                        if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList, pEntry, LL_ACCESS_LOCK ) )
                        {
                            csrReleaseCommandSetKey( pMac, pCommand );
                        }
                    }
                    else
                    {
                        smsLog( pMac, LOGE, "CSR: Roam Completion called but setkey command is not ACTIVE ...\n" );
                    }
                }
                else
                {
                    smsLog( pMac, LOGE, "CSR: SetKey Completion called but NO commands are ACTIVE ...\n" );
                }
                smeProcessPendingQueue( pMac );
            }
            break;
        case eWNI_SME_REMOVEKEY_RSP:
            {
                tSirSmeRemoveKeyRsp *pRsp = (tSirSmeRemoveKeyRsp *)pSirMsg;
                tListElem *pEntry;
                tSmeCmd *pCommand;
                
                pEntry = csrLLPeekHead( &pMac->sme.smeCmdActiveList, LL_ACCESS_LOCK );
                if ( pEntry )
                {
                    pCommand = GET_BASE_ADDR( pEntry, tSmeCmd, Link );
                    if ( eSmeCommandRemoveKey == pCommand->command )
                    {                
                        sessionId = pCommand->sessionId;
                        pSession = CSR_GET_SESSION( pMac, sessionId );

                        if(!pSession)
                        {
                            smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                            return;
                        }
#ifdef FEATURE_WLAN_DIAG_SUPPORT_CSR
                        {
                            WLAN_VOS_DIAG_EVENT_DEF(removeKeyEvent, vos_event_wlan_security_payload_type);
                            palZeroMemory(pMac->hHdd, &removeKeyEvent, sizeof(vos_event_wlan_security_payload_type));
                            removeKeyEvent.eventId = WLAN_SECURITY_EVENT_REMOVE_KEY_RSP;
                            removeKeyEvent.encryptionModeMulticast = 
                                (v_U8_t)diagEncTypeFromCSRType(pSession->connectedProfile.mcEncryptionType);
                            removeKeyEvent.encryptionModeUnicast = 
                                (v_U8_t)diagEncTypeFromCSRType(pSession->connectedProfile.EncryptionType);
                            palCopyMemory( pMac->hHdd, removeKeyEvent.bssid, pSession->connectedProfile.bssid, 6 );
                            removeKeyEvent.authMode = 
                                (v_U8_t)diagAuthTypeFromCSRType(pSession->connectedProfile.AuthType);
                            if( eSIR_SUCCESS != pRsp->statusCode )
                            {
                                removeKeyEvent.status = WLAN_SECURITY_STATUS_FAILURE;
                            }
                            WLAN_VOS_DIAG_EVENT_REPORT(&removeKeyEvent, EVENT_WLAN_SECURITY);
                        }
#endif //FEATURE_WLAN_DIAG_SUPPORT_CSR
                        if( eSIR_SME_SUCCESS == pRsp->statusCode )
                        {
                            palCopyMemory( pMac, &roamInfo.peerMac, &pRsp->peerMacAddr, sizeof(tCsrBssid) );
                            result = eCSR_ROAM_RESULT_NONE;
                            pRoamInfo = &roamInfo;
                        }
                        else
                        {
                            result = eCSR_ROAM_RESULT_FAILURE;
                        }
                        csrRoamCallCallback(pMac, sessionId, &roamInfo, pCommand->u.setKeyCmd.roamId, 
                                            eCSR_ROAM_REMOVE_KEY_COMPLETE, result);
                        if( csrLLRemoveEntry( &pMac->sme.smeCmdActiveList, pEntry, LL_ACCESS_LOCK ) )
                        {
                            csrReleaseCommandRemoveKey( pMac, pCommand );
                        }
                    }
                    else
                    {
                        smsLog( pMac, LOGW, "CSR: Roam Completion called but setkey command is not ACTIVE ...\n" );
                    }
                }
                else
                {
                    smsLog( pMac, LOGW, "CSR: SetKey Completion called but NO commands are ACTIVE ...\n" );
                }
                smeProcessPendingQueue( pMac );
            }
            break;
        case eWNI_SME_GET_STATISTICS_RSP:
            smsLog( pMac, LOG2, FL("Stats rsp from PE\n"));
            csrRoamStatsRspProcessor( pMac, pSirMsg );
            break;
        case eWNI_SME_GET_RSSI_REQ:
            smsLog( pMac, LOG2, FL("GetRssiReq from self\n"));
            csrUpdateRssi( pMac, pSirMsg );
            break;

#ifdef WLAN_FEATURE_VOWIFI_11R
        case eWNI_SME_FT_PRE_AUTH_RSP:
            csrRoamFTPreAuthRspProcessor( pMac, (tpSirFTPreAuthRsp)pSirMsg );
            break;
#endif
        case eWNI_SME_MAX_ASSOC_EXCEEDED:
            pSmeMaxAssocInd = (tSmeMaxAssocInd*)pSirMsg;
            smsLog( pMac, LOG1, FL("send indication that max assoc have been reached and the new peer cannot be accepted\n"));          
            sessionId = pSmeMaxAssocInd->sessionId;
            roamInfo.sessionId = sessionId;
            palCopyMemory(pMac->hHdd, &roamInfo.peerMac, pSmeMaxAssocInd->peerMac, sizeof(tCsrBssid));
            csrRoamCallCallback(pMac, sessionId, &roamInfo, 0, 
                    eCSR_ROAM_INFRA_IND, eCSR_ROAM_RESULT_MAX_ASSOC_EXCEEDED);
            break;
            
        case eWNI_SME_BTAMP_LOG_LINK_IND:
            smsLog( pMac, LOG1, FL("Establish logical link req from HCI serialized through MC thread\n"));
            btampEstablishLogLinkHdlr( pSirMsg );
            break;
        case eWNI_SME_RSSI_IND:
            smsLog( pMac, LOG1, FL("RSSI indication from TL serialized through MC thread\n"));
            csrRoamRssiIndHdlr( pMac, pSirMsg );
        break;

        default:
            break;
    }
