switch (pSirMsg->messageType) 
    {
       case eWNI_SME_GET_STATISTICS_RSP:
          smsLog( pMac, LOG2, FL("Stats rsp from PE\n"));
          csrRoamStatsRspProcessor( pMac, pSirMsg );
          break;
#ifdef WLAN_SOFTAP_FEATURE
        case eWNI_SME_UPPER_LAYER_ASSOC_CNF:
        {
            tCsrRoamSession  *pSession;
            tSirSmeAssocIndToUpperLayerCnf *pUpperLayerAssocCnf;
            tCsrRoamInfo roamInfo;
            tCsrRoamInfo *pRoamInfo = NULL;
            tANI_U32 sessionId;
            eHalStatus status;
            smsLog( pMac, LOG1, FL("ASSOCIATION confirmation can be given to upper layer \n"));
            palZeroMemory(pMac->hHdd, &roamInfo, sizeof(tCsrRoamInfo));
            pRoamInfo = &roamInfo;
            pUpperLayerAssocCnf = (tSirSmeAssocIndToUpperLayerCnf *)pMsgBuf;
            status = csrRoamGetSessionIdFromBSSID( pMac, (tCsrBssid *)pUpperLayerAssocCnf->bssId, &sessionId );
            pSession = CSR_GET_SESSION(pMac, sessionId);

            if(!pSession)
            {
                smsLog(pMac, LOGE, FL("  session %d not found "), sessionId);
                return;
            }
            
            pRoamInfo->statusCode = eSIR_SME_SUCCESS; //send the status code as Success 
            pRoamInfo->u.pConnectedProfile = &pSession->connectedProfile;
            pRoamInfo->staId = (tANI_U8)pUpperLayerAssocCnf->aid;
            pRoamInfo->rsnIELen = (tANI_U8)pUpperLayerAssocCnf->rsnIE.length;
            pRoamInfo->prsnIE = pUpperLayerAssocCnf->rsnIE.rsnIEdata;
            pRoamInfo->addIELen = (tANI_U8)pUpperLayerAssocCnf->addIE.length;
            pRoamInfo->paddIE = pUpperLayerAssocCnf->addIE.addIEdata;           
            palCopyMemory(pMac->hHdd, pRoamInfo->peerMac, pUpperLayerAssocCnf->peerMacAddr, sizeof(tSirMacAddr));
            palCopyMemory(pMac->hHdd, &pRoamInfo->bssid, pUpperLayerAssocCnf->bssId, sizeof(tCsrBssid));
            pRoamInfo->wmmEnabledSta = pUpperLayerAssocCnf->wmmEnabledSta;
            if(CSR_IS_INFRA_AP(pRoamInfo->u.pConnectedProfile) )
            {
                pMac->roam.roamSession[sessionId].connectState = eCSR_ASSOC_STATE_TYPE_INFRA_CONNECTED;
                pRoamInfo->fReassocReq = pUpperLayerAssocCnf->reassocReq;
                status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_INFRA_IND, eCSR_ROAM_RESULT_INFRA_ASSOCIATION_CNF);
            }
            if(CSR_IS_WDS_AP( pRoamInfo->u.pConnectedProfile))
            {
                vos_sleep( 100 );
                pMac->roam.roamSession[sessionId].connectState = eCSR_ASSOC_STATE_TYPE_WDS_CONNECTED;//Sta
                status = csrRoamCallCallback(pMac, sessionId, pRoamInfo, 0, eCSR_ROAM_WDS_IND, eCSR_ROAM_RESULT_WDS_ASSOCIATION_IND);//Sta
            }

        }
        break;
#endif
       default:
          csrRoamCheckForLinkStatusChange( pMac, pSirMsg );
          break;
    }
