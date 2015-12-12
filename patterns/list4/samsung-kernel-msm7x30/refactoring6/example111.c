if (((subType == LIM_ASSOC) &&
         (psessionEntry->limMlmState != eLIM_MLM_WT_ASSOC_RSP_STATE)) ||
        ((subType == LIM_REASSOC) &&
         ((psessionEntry->limMlmState != eLIM_MLM_WT_REASSOC_RSP_STATE) 
#if defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_CCX) || defined(FEATURE_WLAN_LFR)
         && (psessionEntry->limMlmState != eLIM_MLM_WT_FT_REASSOC_RSP_STATE)
#endif
         )))
    {
        /// Received unexpected Re/Association Response frame

#ifdef WLAN_FEATURE_VOWIFI_11R_DEBUG
        PELOG1(limLog(pMac, LOG1,  FL("mlm state is set to %d session=%d\n"), 
            psessionEntry->limMlmState, psessionEntry->peSessionId);)
#endif
        // Log error
        if (!pHdr->fc.retry)
        {
            limLog(pMac, LOGE,
               FL("received Re/Assoc rsp frame in unexpected state\n"));
            limPrintMlmState(pMac, LOGE, psessionEntry->limMlmState);
        }
        palFreeMemory(pMac->hHdd, pBeaconStruct);
        return;
    }
