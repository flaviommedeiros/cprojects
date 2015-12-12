switch(mode)
   {
       case WLAN_HDD_INFRA_STATION:
#ifdef WLAN_FEATURE_P2P
       case WLAN_HDD_P2P_CLIENT:
       case WLAN_HDD_P2P_GO:
#endif
       case WLAN_HDD_SOFTAP:
    pHddCtx->no_of_sessions[mode]--;
    if (!(pHddCtx->no_of_sessions[mode]))
            pHddCtx->concurrency_mode &= (~(1 << mode));
            break;
       default:
            break;
   }
