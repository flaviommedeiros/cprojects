if ( ( pAdapter->device_mode == WLAN_HDD_SOFTAP )
#ifdef WLAN_FEATURE_P2P
      || ( pAdapter->device_mode == WLAN_HDD_P2P_GO )
#endif
       )
    {
        if(params->sta_flags_set & BIT(NL80211_STA_FLAG_AUTHORIZED)) 
        {
            status = hdd_softap_change_STA_state( pAdapter, &STAMacAddress, 
                                                  WLANTL_STA_AUTHENTICATED);

            VOS_TRACE( VOS_MODULE_ID_HDD_SOFTAP, VOS_TRACE_LEVEL_ERROR,
                "%s: Station MAC address does not matching", __FUNCTION__);
            return -EINVAL;
        }
    }
