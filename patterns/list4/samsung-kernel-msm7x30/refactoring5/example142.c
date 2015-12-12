#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
       pParams->qosInfo =
           (psessionEntry->apUapsdEnable << 7) | ((tANI_U8)(0x0f & psessionEntry->gLimEdcaParamSetCount));
    else
#endif
       pParams->qosInfo =
           (pMac->lim.gUapsdEnable << 7) | ((tANI_U8)(0x0f & psessionEntry->gLimEdcaParamSetCount));
