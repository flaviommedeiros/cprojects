if ( 
#ifdef FEATURE_WLAN_CCX
        ((pNeighborRoamInfo->isCCXAssoc) && 
                    (pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived == eANI_BOOLEAN_FALSE)) ||
        (pNeighborRoamInfo->isCCXAssoc == eANI_BOOLEAN_FALSE) || 
#endif // CCX
        pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels == 0)

    {
        smsLog(pMac, LOGW, FL("Falling back to CFG channel list"));


        /* Free up the channel list and allocate a new memory. This is because we dont know how much 
            was allocated last time. If we directly copy more number of bytes than allocated earlier, this might 
            result in memory corruption */
        if (NULL != pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList)
        {
            vos_mem_free(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList);
            pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
        }
        VOS_ASSERT( pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList == NULL);

        // Now obtain the contents for "channelList" (the "default valid channel list") from EITHER
        // the gNeighborScanChannelList in "cfg.ini", OR the actual "valid channel list" information formed by CSR.
        if (0 != pNeighborRoamInfo->cfgParams.channelInfo.numOfChannels)
        {
            // Copy the "default valid channel list" (channelList) from the gNeighborScanChannelList in "cfg.ini".
            NEIGHBOR_ROAM_DEBUG(pMac, LOGE, "Using the channel list from cfg.ini");
            status = csrNeighborRoamMergeChannelLists( 
                    pMac, 
                    pNeighborRoamInfo->cfgParams.channelInfo.ChannelList, 
                    pNeighborRoamInfo->cfgParams.channelInfo.numOfChannels, 
                    channelList, 
                    0, //NB: If 0, simply copy the input channel list to the output list.
                    &numOfChannels );
        } 
        else
            {
            /* Get current list of valid channels. */
            NEIGHBOR_ROAM_DEBUG(pMac, LOGE, "Switching to master list of valid channels");
            numOfChannels = sizeof(pMac->roam.validChannelList);
            if(HAL_STATUS_SUCCESS(csrGetCfgValidChannels(pMac, (tANI_U8 *)pMac->roam.validChannelList, (tANI_U32 *) &numOfChannels)))
            {
                // Copy the "default valid channel list" (channelList) from the actual "valid channel list" information formed by CSR
                status = csrNeighborRoamMergeChannelLists( 
                        pMac, 
                        (tANI_U8 *)pMac->roam.validChannelList, 
                        numOfChannels,   // The number of channels in the validChannelList 
                        channelList, 
                        0, //NB: If 0, simply copy the input channel list to the output list.
                        &numOfChannels );  // The final number of channels in the output list. Will be numOfChannels
            }
            else
            { 
                smsLog(pMac, LOGE, FL("Could not get valid channel list, TL event ignored")); 
                return VOS_STATUS_E_FAILURE;
            }
        }

        /* At this point, channelList contains our best inputs on the "valid channel list" */

        /* Allocate for the maximum number that might be used */
        smsLog(pMac, LOGE, FL("%d channels in the default list. Add %d occupied channels. %d is the MAX scan channel list."), 
                numOfChannels, 
                CSR_BG_SCAN_OCCUPIED_CHANNEL_LIST_LEN, 
                numOfChannels+CSR_BG_SCAN_OCCUPIED_CHANNEL_LIST_LEN );
        pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = numOfChannels;
        VOS_ASSERT( pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList == NULL);
        if (numOfChannels)
        {
            pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = 
                vos_mem_malloc(numOfChannels+CSR_BG_SCAN_OCCUPIED_CHANNEL_LIST_LEN );
        }
    
        if (NULL == pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList)
        {
            smsLog(pMac, LOGE, FL("Memory allocation for Channel list failed.. TL event ignored"));
            return VOS_STATUS_E_RESOURCES;
        }
    
#ifdef FEATURE_WLAN_LFR
        /* Since this is a legacy case, copy the channel list from CFG here */
    
        status = csrNeighborRoamReorderChannelList( pMac, 
                channelList, 
                numOfChannels, 
                pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList, 
                &numOfChannels );
        if (eHAL_STATUS_SUCCESS != status)
#endif
        {
            /* Re-ordering failed. */
            smsLog(pMac, LOGE, FL("Cannot re-order scan channel list. (status = %d) Going to use default scan channel list."), status);
        vos_mem_copy(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList, 
                                channelList, numOfChannels * sizeof(tANI_U8));
        } 

        /* Adjust for the actual number that are used */
        pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = numOfChannels;
        for (i = 0; i < pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels; i++)
        {
            NEIGHBOR_ROAM_DEBUG(pMac, LOGE, "Channel List from CFG (or scan caching) = %d\n", 
                pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList[i]);
        }
    }
