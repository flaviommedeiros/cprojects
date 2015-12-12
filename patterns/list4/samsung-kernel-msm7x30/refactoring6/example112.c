if ((subType == LIM_ASSOC)
#ifdef WLAN_FEATURE_VOWIFI_11R
                    || ((subType == LIM_REASSOC) && (psessionEntry->limMlmState == eLIM_MLM_WT_FT_REASSOC_RSP_STATE))
#endif
       ) {
        PELOGE(limLog(pMac, LOGE,  FL("Assoc Rejected by the peer. Reason: %d\n"), mlmAssocCnf.resultCode);)
        psessionEntry->limMlmState = eLIM_MLM_IDLE_STATE;
        MTRACE(macTrace(pMac, TRACE_CODE_MLM_STATE, psessionEntry->peSessionId, psessionEntry->limMlmState));

        if (psessionEntry->pLimMlmJoinReq)
        {
            palFreeMemory( pMac->hHdd, psessionEntry->pLimMlmJoinReq);
            psessionEntry->pLimMlmJoinReq = NULL;
        }

        if (subType == LIM_ASSOC)
        {
           limPostSmeMessage(pMac, LIM_MLM_ASSOC_CNF, (tANI_U32 *) &mlmAssocCnf);
        }
#ifdef WLAN_FEATURE_VOWIFI_11R
        else
        {
                mlmAssocCnf.resultCode = eSIR_SME_FT_REASSOC_FAILURE;
                limPostSmeMessage(pMac, LIM_MLM_REASSOC_CNF, (tANI_U32 *) &mlmAssocCnf);
        }
#endif /* WLAN_FEATURE_VOWIFI_11R */
    } else {
        limRestorePreReassocState( pMac, 
                  eSIR_SME_REASSOC_REFUSED, mlmAssocCnf.protStatusCode,psessionEntry); 
    }
