if(( pSession->connectedProfile.BSSType == eCSR_BSS_TYPE_INFRASTRUCTURE ) || 
          ( pSession->connectedProfile.BSSType == eCSR_BSS_TYPE_IBSS ) ||
#ifdef WLAN_SOFTAP_FEATURE	  
          ( pSession->connectedProfile.BSSType == eCSR_BSS_TYPE_INFRA_AP ) ||
#endif
          ( pSession->connectedProfile.BSSType == eCSR_BSS_TYPE_START_IBSS ))
       {
           *pChannel =pSession->connectedProfile.operationChannel;
           return eHAL_STATUS_SUCCESS;
       }
