if((pAdapter->device_mode == WLAN_HDD_SOFTAP)
#ifdef WLAN_FEATURE_P2P
     ||  (pAdapter->device_mode == WLAN_HDD_P2P_GO)
#endif
      ) 
    {
        /* ap_isolate == -1 means that in change bss, upper layer doesn't
         * want to update this parameter */
        if (-1 != params->ap_isolate) 
        {
            pAdapter->sessionCtx.ap.apDisableIntraBssFwd = !!params->ap_isolate;
        } 
    }
