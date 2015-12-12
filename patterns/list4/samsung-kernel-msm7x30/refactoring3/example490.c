switch(wdiLowLevelInd->wdiIndicationType)
   {
      case WDI_RSSI_NOTIFICATION_IND:
      {
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                     "Received WDI_HAL_RSSI_NOTIFICATION_IND from WDI ");
#if defined WLAN_FEATURE_NEIGHBOR_ROAMING
         rssiNotification.bReserved = 
            wdiLowLevelInd->wdiIndicationData.wdiLowRSSIInfo.bReserved;
         rssiNotification.bRssiThres1NegCross = 
            wdiLowLevelInd->wdiIndicationData.wdiLowRSSIInfo.bRssiThres1NegCross;
         rssiNotification.bRssiThres1PosCross = 
            wdiLowLevelInd->wdiIndicationData.wdiLowRSSIInfo.bRssiThres1PosCross;
         rssiNotification.bRssiThres2NegCross = 
            wdiLowLevelInd->wdiIndicationData.wdiLowRSSIInfo.bRssiThres2NegCross;
         rssiNotification.bRssiThres2PosCross = 
            wdiLowLevelInd->wdiIndicationData.wdiLowRSSIInfo.bRssiThres2PosCross;
         rssiNotification.bRssiThres3NegCross = 
            wdiLowLevelInd->wdiIndicationData.wdiLowRSSIInfo.bRssiThres3NegCross;
         rssiNotification.bRssiThres3PosCross = 
            wdiLowLevelInd->wdiIndicationData.wdiLowRSSIInfo.bRssiThres3PosCross;
         WLANTL_BMPSRSSIRegionChangedNotification(
            pWDA->pVosContext,
            &rssiNotification);
#endif
         break ;
      }
      case WDI_MISSED_BEACON_IND:
      {
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                     "Received WDI_MISSED_BEACON_IND from WDI ");
         /* send IND to PE */
         WDA_SendMsg(pWDA, WDA_MISSED_BEACON_IND, NULL, 0) ;
         break ;
      }
      case WDI_UNKNOWN_ADDR2_FRAME_RX_IND:
      {
         /* TODO: Decode Ind and send Ind to PE */
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                     "Received WDI_UNKNOWN_ADDR2_FRAME_RX_IND from WDI ");
         break ;
      }
       
      case WDI_MIC_FAILURE_IND:
      {
         tpSirSmeMicFailureInd pMicInd =
           (tpSirSmeMicFailureInd)vos_mem_malloc(sizeof(tSirSmeMicFailureInd));

         if(NULL == pMicInd)
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                                  "%s: VOS MEM Alloc Failure", __FUNCTION__);
            break;
         }
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                                  "Received WDI_MIC_FAILURE_IND from WDI ");
         pMicInd->messageType = eWNI_SME_MIC_FAILURE_IND;
         pMicInd->length = sizeof(tSirSmeMicFailureInd);
         vos_mem_copy(pMicInd->bssId,
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.bssId,
             sizeof(tSirMacAddr));
         vos_mem_copy(pMicInd->info.srcMacAddr,
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.macSrcAddr,
             sizeof(tSirMacAddr));
         vos_mem_copy(pMicInd->info.taMacAddr,
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.macTaAddr,
             sizeof(tSirMacAddr));
         vos_mem_copy(pMicInd->info.dstMacAddr,
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.macDstAddr,
             sizeof(tSirMacAddr));
         vos_mem_copy(pMicInd->info.rxMacAddr,
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.macRxAddr,
             sizeof(tSirMacAddr));
         pMicInd->info.multicast = 
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.ucMulticast;
         pMicInd->info.keyId= 
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.keyId;
         pMicInd->info.IV1= 
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.ucIV1;
         vos_mem_copy(pMicInd->info.TSC,
             wdiLowLevelInd->wdiIndicationData.wdiMICFailureInfo.TSC,SIR_CIPHER_SEQ_CTR_SIZE);
         WDA_SendMsg(pWDA, SIR_HAL_MIC_FAILURE_IND, 
                                       (void *)pMicInd , 0) ;
         break ;
      }
      case WDI_FATAL_ERROR_IND:
      {
         /* TODO: Decode Ind and send Ind to PE */
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                                  "Received WDI_FATAL_ERROR_IND from WDI ");
         break ;
      }
      case WDI_DEL_STA_IND:
      {
         tpDeleteStaContext  pDelSTACtx = 
            (tpDeleteStaContext)vos_mem_malloc(sizeof(tDeleteStaContext));
         
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                                  "Received WDI_DEL_STA_IND from WDI ");
         if(NULL == pDelSTACtx)
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                                  "%s: VOS MEM Alloc Failure", __FUNCTION__);
            break;
         }
         vos_mem_copy(pDelSTACtx->addr2,
             wdiLowLevelInd->wdiIndicationData.wdiDeleteSTAIndType.macADDR2,
             sizeof(tSirMacAddr));
         vos_mem_copy(pDelSTACtx->bssId,
             wdiLowLevelInd->wdiIndicationData.wdiDeleteSTAIndType.macBSSID,
             sizeof(tSirMacAddr));
         pDelSTACtx->assocId    = 
          wdiLowLevelInd->wdiIndicationData.wdiDeleteSTAIndType.usAssocId;
         pDelSTACtx->reasonCode = 
          wdiLowLevelInd->wdiIndicationData.wdiDeleteSTAIndType.wptReasonCode;
         pDelSTACtx->staId      = 
          wdiLowLevelInd->wdiIndicationData.wdiDeleteSTAIndType.ucSTAIdx;
         WDA_SendMsg(pWDA, SIR_LIM_DELETE_STA_CONTEXT_IND, 
                                       (void *)pDelSTACtx , 0) ;
         break ;
      }
      case WDI_COEX_IND:
      {
         tANI_U32 index;
         vos_msg_t vosMsg;
         tSirSmeCoexInd *pSmeCoexInd = (tSirSmeCoexInd *)vos_mem_malloc(sizeof(tSirSmeCoexInd));
         if(NULL == pSmeCoexInd)
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                             "%s: VOS MEM Alloc Failure-pSmeCoexInd", __FUNCTION__);
            break;
         }
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                                  "Received WDI_COEX_IND from WDI ");
         /* Message Header */
         pSmeCoexInd->mesgType = eWNI_SME_COEX_IND;
         pSmeCoexInd->mesgLen = sizeof(tSirSmeCoexInd);
         /* Info from WDI Indication */
         pSmeCoexInd->coexIndType = wdiLowLevelInd->wdiIndicationData.wdiCoexInfo.coexIndType; 
         for (index = 0; index < SIR_COEX_IND_DATA_SIZE; index++)
         {
            pSmeCoexInd->coexIndData[index] = wdiLowLevelInd->wdiIndicationData.wdiCoexInfo.coexIndData[index]; 
         }
         /* VOS message wrapper */
         vosMsg.type = eWNI_SME_COEX_IND;
         vosMsg.bodyptr = (void *)pSmeCoexInd;
         vosMsg.bodyval = 0;
         /* Send message to SME */
         if (VOS_STATUS_SUCCESS != vos_mq_post_message(VOS_MQ_ID_SME, (vos_msg_t*)&vosMsg))
         {
            /* free the mem and return */
            vos_mem_free((v_VOID_t *)pSmeCoexInd);
         }
         else
         {
            /* DEBUG */
            VOS_TRACE(VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                      "[COEX WDA] Coex Ind Type (%x) data (%x %x %x %x)",
                      pSmeCoexInd->coexIndType, 
                      pSmeCoexInd->coexIndData[0], 
                      pSmeCoexInd->coexIndData[1], 
                      pSmeCoexInd->coexIndData[2], 
                      pSmeCoexInd->coexIndData[3]); 
         }
         break;
      }
      case WDI_TX_COMPLETE_IND:
      {
         tpAniSirGlobal pMac = (tpAniSirGlobal )VOS_GET_MAC_CTXT(pWDA->pVosContext) ;
         /* Calling TxCompleteAck Indication from wda context*/
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                        "Complete Indication received from HAL");
         if( pWDA->pAckTxCbFunc )
         {
            if( VOS_STATUS_SUCCESS !=
                              WDA_STOP_TIMER(&pWDA->wdaTimers.TxCompleteTimer))
            {  
               VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                                  "Tx Complete timeout Timer Stop Failed ");
            }  
            pWDA->pAckTxCbFunc( pMac, wdiLowLevelInd->wdiIndicationData.tx_complete_status);
            pWDA->pAckTxCbFunc = NULL;
         }
         else
         {
             VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                          "Tx Complete Indication is received after timeout ");
         }
         break;
      }
#ifdef WLAN_FEATURE_P2P
      case WDI_P2P_NOA_ATTR_IND :
      {
         tSirP2PNoaAttr   *pP2pNoaAttr = 
            (tSirP2PNoaAttr *)vos_mem_malloc(sizeof(tSirP2PNoaAttr));
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                              "Received WDI_P2P_NOA_ATTR_IND from WDI");
         if (NULL == pP2pNoaAttr)
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                       "Memory allocation failure, "
                       "WDI_P2P_NOA_ATTR_IND not forwarded");
            break;
         }
         pP2pNoaAttr->index            = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.ucIndex;
         pP2pNoaAttr->oppPsFlag        = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.ucOppPsFlag;
         pP2pNoaAttr->ctWin            = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.usCtWin;
         
         pP2pNoaAttr->uNoa1IntervalCnt = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.usNoa1IntervalCnt;
         pP2pNoaAttr->uNoa1Duration    = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.uslNoa1Duration;
         pP2pNoaAttr->uNoa1Interval    = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.uslNoa1Interval;
         pP2pNoaAttr->uNoa1StartTime   = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.uslNoa1StartTime;
         pP2pNoaAttr->uNoa2IntervalCnt = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.usNoa2IntervalCnt;
         pP2pNoaAttr->uNoa2Duration    = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.uslNoa2Duration;
         pP2pNoaAttr->uNoa2Interval    = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.uslNoa2Interval;
         pP2pNoaAttr->uNoa2StartTime   = 
                    wdiLowLevelInd->wdiIndicationData.wdiP2pNoaAttrInfo.uslNoa2StartTime;
         WDA_SendMsg(pWDA, SIR_HAL_P2P_NOA_ATTR_IND, 
                                       (void *)pP2pNoaAttr , 0) ;
         break;
      }
#endif
#ifdef FEATURE_WLAN_SCAN_PNO
      case WDI_PREF_NETWORK_FOUND_IND:
      {
         vos_msg_t vosMsg;
         tSirPrefNetworkFoundInd *pPrefNetworkFoundInd = (tSirPrefNetworkFoundInd *)vos_mem_malloc(sizeof(tSirPrefNetworkFoundInd));
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO,
                              "Received WDI_PREF_NETWORK_FOUND_IND from WDI");
         if (NULL == pPrefNetworkFoundInd)
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                       "Memory allocation failure, "
                       "WDI_PREF_NETWORK_FOUND_IND not forwarded");
            break;
         }
         /* Message Header */
         pPrefNetworkFoundInd->mesgType = eWNI_SME_PREF_NETWORK_FOUND_IND;
         pPrefNetworkFoundInd->mesgLen = sizeof(*pPrefNetworkFoundInd);

         /* Info from WDI Indication */ 
         pPrefNetworkFoundInd->ssId.length = 
            wdiLowLevelInd->wdiIndicationData.wdiPrefNetworkFoundInd.ssId.ucLength;
         vos_mem_set( pPrefNetworkFoundInd->ssId.ssId, 32, 0);
         vos_mem_copy( pPrefNetworkFoundInd->ssId.ssId, 
                  wdiLowLevelInd->wdiIndicationData.wdiPrefNetworkFoundInd.ssId.sSSID, 
                  pPrefNetworkFoundInd->ssId.length);
         pPrefNetworkFoundInd ->rssi = wdiLowLevelInd->wdiIndicationData.wdiPrefNetworkFoundInd.rssi; 
         /* VOS message wrapper */
         vosMsg.type = eWNI_SME_PREF_NETWORK_FOUND_IND;
         vosMsg.bodyptr = (void *) pPrefNetworkFoundInd;
         vosMsg.bodyval = 0;
         /* Send message to SME */
         if (VOS_STATUS_SUCCESS != vos_mq_post_message(VOS_MQ_ID_SME, (vos_msg_t*)&vosMsg))
         {
            /* free the mem and return */
            vos_mem_free((v_VOID_t *) pPrefNetworkFoundInd);
         }
         break;
      }
#endif // FEATURE_WLAN_SCAN_PNO
      
#ifdef WLAN_WAKEUP_EVENTS
      case WDI_WAKE_REASON_IND:
      {
         vos_msg_t vosMsg;
         tANI_U32 allocSize = sizeof(tSirWakeReasonInd) 
                                  + (wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulStoredDataLen - 1);
         tSirWakeReasonInd *pWakeReasonInd = (tSirWakeReasonInd *)vos_mem_malloc(allocSize);

         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                    "[WAKE_REASON WDI] WAKE_REASON_IND Type (0x%x) data (ulReason=0x%x, ulReasonArg=0x%x, ulStoredDataLen=0x%x)",
                    wdiLowLevelInd->wdiIndicationType,
                    wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulReason,
                    wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulReasonArg,
                    wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulStoredDataLen);

         if (NULL == pWakeReasonInd)
         {
            VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                       "Memory allocation failure, "
                       "WDI_WAKE_REASON_IND not forwarded");
            break;
         }

         vos_mem_zero(pWakeReasonInd, allocSize);

         /* Message Header */
         pWakeReasonInd->mesgType = eWNI_SME_WAKE_REASON_IND;
         pWakeReasonInd->mesgLen = allocSize;

         /* Info from WDI Indication */
         // Fill pWakeReasonInd structure from wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd
         pWakeReasonInd->ulReason = wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulReason;
         pWakeReasonInd->ulReasonArg = wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulReasonArg;
         pWakeReasonInd->ulStoredDataLen = wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulStoredDataLen;
         pWakeReasonInd->ulActualDataLen = wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulActualDataLen;         
         vos_mem_copy( (void *)&(pWakeReasonInd->aDataStart[0]), 
                        &(wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.aDataStart[0]), 
                        wdiLowLevelInd->wdiIndicationData.wdiWakeReasonInd.ulStoredDataLen);

         /* VOS message wrapper */
         vosMsg.type = eWNI_SME_WAKE_REASON_IND;
         vosMsg.bodyptr = (void *) pWakeReasonInd;
         vosMsg.bodyval = 0;

         /* Send message to SME */
         if (VOS_STATUS_SUCCESS != vos_mq_post_message(VOS_MQ_ID_SME, (vos_msg_t*)&vosMsg))
         {
            /* free the mem and return */
            vos_mem_free((v_VOID_t *) pWakeReasonInd);
         }

         break;
      }
#endif // WLAN_WAKEUP_EVENTS
      
      case WDI_TX_PER_HIT_IND:
      {
         vos_msg_t vosMsg;
         VOS_TRACE(VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_INFO, "Get WDI_TX_PER_HIT_IND");
         /* send IND to PE eWNI_SME_TX_PER_HIT_IND*/
         /* VOS message wrapper */
         vosMsg.type = eWNI_SME_TX_PER_HIT_IND;
         vosMsg.bodyptr = NULL;
         vosMsg.bodyval = 0;
         /* Send message to SME */
         if (VOS_STATUS_SUCCESS != vos_mq_post_message(VOS_MQ_ID_SME, (vos_msg_t*)&vosMsg))
         {
            VOS_TRACE(VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_WARN, "post eWNI_SME_TX_PER_HIT_IND to SME Failed");
         }
         break;
      }
  
      default:
      {
         /* TODO error */
         VOS_TRACE( VOS_MODULE_ID_WDA, VOS_TRACE_LEVEL_ERROR,
                                  "Received UNKNOWN Indication from WDI ");
      } 
   }
