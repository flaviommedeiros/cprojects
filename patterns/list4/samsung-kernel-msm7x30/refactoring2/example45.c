#ifdef FEATURE_WLAN_LFR
if (eHAL_STATUS_SUCCESS != status)
#endif
        {
            /* Re-ordering failed. */
            smsLog(pMac, LOGE, FL("Cannot re-order scan channel list. (status = %d) Going to use default scan channel list."), status);
        vos_mem_copy(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList, 
                                channelList, numOfChannels * sizeof(tANI_U8));
        }
