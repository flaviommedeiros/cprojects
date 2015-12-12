if  ( (psessionEntry->limSystemRole == eLIM_STA_ROLE ) && 
          ( 
#ifdef FEATURE_WLAN_CCX
          (psessionEntry->isCCXconnection ) || 
#endif
#ifdef FEATURE_WLAN_LFR
          (psessionEntry->isFastRoamIniFeatureEnabled ) ||
#endif
          (psessionEntry->is11Rconnection )) &&
          (pMlmDisassocReq->reasonCode != eSIR_MAC_DISASSOC_DUE_TO_FTHANDOFF_REASON))
    {
          PELOGE(limLog(pMac, LOGE, FL("FT Preauth Session (%p,%d) Cleanup\n"),
                 psessionEntry, psessionEntry->peSessionId);)
          limFTCleanup(pMac);
    }
    else 
    {
          PELOGE(limLog(pMac, LOGE, FL("No FT Preauth Session Cleanup in role %d"
#ifdef FEATURE_WLAN_CCX
                 " isCCX %d"
#endif
#ifdef FEATURE_WLAN_LFR
                 " isLFR %d"
#endif
                 " is11r %d reason %d\n"),
                 psessionEntry->limSystemRole, 
#ifdef FEATURE_WLAN_CCX
                 psessionEntry->isCCXconnection,
#endif
#ifdef FEATURE_WLAN_LFR
                 psessionEntry->isFastRoamIniFeatureEnabled,
#endif
                 psessionEntry->is11Rconnection,
                 pMlmDisassocReq->reasonCode);)
    }
