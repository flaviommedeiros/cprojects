if ((WLAN_HDD_SOFTAP != pAdapter->device_mode)
#ifdef WLAN_FEATURE_P2P
     && (WLAN_HDD_P2P_GO != pAdapter->device_mode)
#endif
      )
    {
        if(VOS_STATUS_SUCCESS != wlan_hdd_validate_operation_channel(pAdapter,channel))
        {
            hddLog(VOS_TRACE_LEVEL_ERROR,
                    "%s: Invalid Channel [%d] \n", __func__, channel);
            return -EINVAL;
        }
        hddLog(VOS_TRACE_LEVEL_INFO_HIGH, 
                "%s: set channel to [%d] for device mode =%d", 
                          __func__, channel,pAdapter->device_mode);
    }
