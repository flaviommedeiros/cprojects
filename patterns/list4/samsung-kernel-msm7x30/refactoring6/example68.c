if ((pAdapter->device_mode == WLAN_HDD_SOFTAP) 
#ifdef WLAN_FEATURE_P2P
      || (pAdapter->device_mode == WLAN_HDD_P2P_GO)
#endif
       )
    {
        beacon_data_t  *old,*new;

        old = pAdapter->sessionCtx.ap.beacon;
   
        if (old)
            return -EALREADY;

        status = wlan_hdd_cfg80211_alloc_new_beacon(pAdapter, &new, &params->beacon, params->dtim_period);

        if(status != VOS_STATUS_SUCCESS) 
        {
             hddLog(VOS_TRACE_LEVEL_FATAL,
                   "%s:Error!!! Allocating the new beacon\n",__func__);
             return -EINVAL;
        }
        pAdapter->sessionCtx.ap.beacon = new;
        status = wlan_hdd_cfg80211_start_bss(pAdapter, &params->beacon, params->ssid,
                                             params->ssid_len, params->hidden_ssid);
    }
