if ((pAdapter->device_mode == WLAN_HDD_SOFTAP)
#ifdef WLAN_FEATURE_P2P
     || (pAdapter->device_mode == WLAN_HDD_P2P_GO)
#endif
       )
    {
        beacon_data_t *old;

        old = pAdapter->sessionCtx.ap.beacon;

        if (!old)
            return -ENOENT;

#ifdef CONFIG_CFG80211
        hdd_cleanup_actionframe(pHddCtx, pAdapter);
#endif

        mutex_lock(&pHddCtx->sap_lock);
        if(test_bit(SOFTAP_BSS_STARTED, &pAdapter->event_flags))
        {
            if ( VOS_STATUS_SUCCESS == (status = WLANSAP_StopBss((WLAN_HDD_GET_CTX(pAdapter))->pvosContext) ) )
            {
                hdd_hostapd_state_t *pHostapdState = WLAN_HDD_GET_HOSTAP_STATE_PTR(pAdapter);

                status = vos_wait_single_event(&pHostapdState->vosEvent, 10000);

                if (!VOS_IS_STATUS_SUCCESS(status))
                {
                    VOS_TRACE(VOS_MODULE_ID_HDD, VOS_TRACE_LEVEL_ERROR,
                             ("ERROR: HDD vos wait for single_event failed!!\n"));
                    VOS_ASSERT(0);
                }
            }
            clear_bit(SOFTAP_BSS_STARTED, &pAdapter->event_flags);
        }
        mutex_unlock(&pHddCtx->sap_lock);

        if(status != VOS_STATUS_SUCCESS)
        {
            hddLog(VOS_TRACE_LEVEL_FATAL,
                    "%s:Error!!! Stopping the BSS\n",__func__);
            return -EINVAL;
        }

        if (ccmCfgSetInt((WLAN_HDD_GET_CTX(pAdapter))->hHal,
            WNI_CFG_PROBE_RSP_BCN_ADDNIE_FLAG, 0,NULL, eANI_BOOLEAN_FALSE)
                                                    ==eHAL_STATUS_FAILURE)
        {
            hddLog(LOGE,
               "Could not pass on WNI_CFG_PROBE_RSP_BCN_ADDNIE_FLAG to CCM\n");
        }

        if ( eHAL_STATUS_FAILURE == ccmCfgSetInt((WLAN_HDD_GET_CTX(pAdapter))->hHal,
                            WNI_CFG_ASSOC_RSP_ADDNIE_FLAG, 0, NULL,
                            eANI_BOOLEAN_FALSE) )
        {
            hddLog(LOGE,
               "Could not pass on WNI_CFG_ASSOC_RSP_ADDNIE_FLAG to CCM\n");
        }

        // Reset WNI_CFG_PROBE_RSP Flags
        wlan_hdd_reset_prob_rspies(pAdapter);

        pAdapter->sessionCtx.ap.beacon = NULL;
        kfree(old);
    }
