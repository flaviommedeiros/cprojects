#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE )
        pParams->acvo_aifsn     = ( 0xf & psessionEntry->gLimEdcaParamsBC[3].aci.aifsn );
    else
#endif
        pParams->acvo_aifsn     = ( 0xf & SET_AIFSN(psessionEntry->gLimEdcaParamsBC[3].aci.aifsn) );
