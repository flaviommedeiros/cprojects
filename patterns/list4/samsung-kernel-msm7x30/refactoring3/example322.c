switch (pNeighborRoamInfo->neighborRoamState)
    {
#ifdef WLAN_FEATURE_VOWIFI_11R
        case eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN:
            switch(pNeighborRoamInfo->prevNeighborRoamState)
            {
                case eCSR_NEIGHBOR_ROAM_STATE_REPORT_QUERY:
                    csrNeighborRoamPerformBgScan(pMac);
                    break;
                default:
                    smsLog(pMac, LOGE, FL("Neighbor scan callback received in state %d, prev state = %d"), 
                                    pNeighborRoamInfo->neighborRoamState, pNeighborRoamInfo->prevNeighborRoamState);
                    break;
            }
            break;
#endif /* WLAN_FEATURE_VOWIFI_11R */
        case eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN:     
            csrNeighborRoamPerformBgScan(pMac);
            break;
        default:
            break;
    }
