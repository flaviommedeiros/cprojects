if ( (WLAN_HDD_SOFTAP == pAdapter->device_mode)
#ifdef WLAN_FEATURE_P2P
       || (WLAN_HDD_P2P_GO == pAdapter->device_mode)
#endif
       )
    {
        if( NULL == mac )
        {
            v_U16_t i;
            for(i = 0; i < WLAN_MAX_STA_COUNT; i++)
            {
                if(pAdapter->aStaInfo[i].isUsed)
                {
                    u8 *macAddr = pAdapter->aStaInfo[i].macAddrSTA.bytes;
                    hddLog(VOS_TRACE_LEVEL_INFO,
                                        "%s: Delete STA with MAC::"
                                        "%02x:%02x:%02x:%02x:%02x:%02x",
                                        __func__,
                                        macAddr[0], macAddr[1], macAddr[2],
                                        macAddr[3], macAddr[4], macAddr[5]);
                    hdd_softap_sta_deauth(pAdapter, macAddr);
                }
            }
        }
        else
        {
            hddLog(VOS_TRACE_LEVEL_INFO,
                                "%s: Delete STA with MAC::"
                                "%02x:%02x:%02x:%02x:%02x:%02x",
                                __func__,
                                mac[0], mac[1], mac[2],
                                mac[3], mac[4], mac[5]);
            hdd_softap_sta_deauth(pAdapter, mac);
        }
    }
