#ifdef WLAN_SOFTAP_FEATURE
if (VOS_STA_SAP_MODE == hdd_get_conparam())
    {
        status = hdd_get_front_adapter ( pHddCtx, &pAdapterNode );
        if ( NULL != pAdapterNode && VOS_STATUS_SUCCESS == status )
        {
            if ( WLAN_HDD_SOFTAP == pAdapterNode->pAdapter->device_mode)
            {
                pAdapter = hdd_get_adapter(pHddCtx, WLAN_HDD_SOFTAP);
            }
            else if (WLAN_HDD_P2P_GO == pAdapterNode->pAdapter->device_mode)
            {
                pAdapter = hdd_get_adapter(pHddCtx, WLAN_HDD_P2P_GO);
            }
        }
     }
    else
#endif
        pAdapter = hdd_get_adapter(pHddCtx, WLAN_HDD_INFRA_STATION);
