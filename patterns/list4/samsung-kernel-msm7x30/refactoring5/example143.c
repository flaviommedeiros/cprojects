#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE )
        pParams->acvi_aifsn     = ( 0xf & psessionEntry->gLimEdcaParamsBC[2].aci.aifsn );
    else
#endif
        pParams->acvi_aifsn     = ( 0xf & SET_AIFSN(psessionEntry->gLimEdcaParamsBC[2].aci.aifsn) );
