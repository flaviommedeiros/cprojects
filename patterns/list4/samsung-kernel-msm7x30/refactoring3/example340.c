switch(ind)
   {
      case SME_QOS_CSR_ASSOC_COMPLETE:
         //expecting assoc info in pEvent_info
         status = sme_QosProcessAssocCompleteEv(pMac, sessionId, pEvent_info);
         break;
      case SME_QOS_CSR_REASSOC_REQ:
         //nothing expected in pEvent_info
         status = sme_QosProcessReassocReqEv(pMac, sessionId, pEvent_info);
         break;
      case SME_QOS_CSR_REASSOC_COMPLETE:
         //expecting assoc info in pEvent_info
         status = sme_QosProcessReassocSuccessEv(pMac, sessionId, pEvent_info);
         break;
      case SME_QOS_CSR_REASSOC_FAILURE:
         //nothing expected in pEvent_info
         status = sme_QosProcessReassocFailureEv(pMac, sessionId, pEvent_info);
         break;
      case SME_QOS_CSR_DISCONNECT_REQ:
      case SME_QOS_CSR_DISCONNECT_IND:
         //nothing expected in pEvent_info
         status = sme_QosProcessDisconnectEv(pMac, sessionId, pEvent_info);
         break;
      case SME_QOS_CSR_JOIN_REQ:
         //nothing expected in pEvent_info
         status = sme_QosProcessJoinReqEv(pMac, sessionId, pEvent_info);
         break;
      case SME_QOS_CSR_HANDOFF_ASSOC_REQ:
         //nothing expected in pEvent_info
         status = sme_QosProcessHandoffAssocReqEv(pMac, sessionId, pEvent_info);
         break;
      case SME_QOS_CSR_HANDOFF_COMPLETE:
         //nothing expected in pEvent_info
         status = sme_QosProcessHandoffSuccessEv(pMac, sessionId, pEvent_info);
         break;
      case SME_QOS_CSR_HANDOFF_FAILURE:
         //nothing expected in pEvent_info
         status = sme_QosProcessHandoffFailureEv(pMac, sessionId, pEvent_info);
         break;
#ifdef WLAN_FEATURE_VOWIFI_11R
      case SME_QOS_CSR_PREAUTH_SUCCESS_IND:
         status = sme_QosProcessPreauthSuccessInd(pMac, sessionId, pEvent_info);
         break;
#if defined(FEATURE_WLAN_CCX) || defined(FEATURE_WLAN_LFR)
      case SME_QOS_CSR_SET_KEY_SUCCESS_IND:
         status = sme_QosProcessSetKeySuccessInd(pMac, sessionId, pEvent_info);
         break;
#endif
#endif
      default:
         //Err msg
         VOS_TRACE(VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_ERROR, 
                   "%s: %d: On Session %d Unknown Event %d received from CSR",
                   __FUNCTION__, __LINE__,
                   sessionId, ind );
         break;
   }
