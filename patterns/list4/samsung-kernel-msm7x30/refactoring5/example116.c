#ifdef FEATURE_WLAN_LFR
if (csrRoamIsFastRoamEnabled(pMac))
    {
        if (eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN == pNeighborRoamInfo->neighborRoamState)
        {
            csrNeighborRoamIssuePreauthReq(pMac);
        }
        else
        {
            smsLog(pMac, LOGE, FL("LFR Reassoc indication received in unexpected state %d"), pNeighborRoamInfo->neighborRoamState);
            VOS_ASSERT(0);
        }
    }
    else
#endif
    {
        if (eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN == pNeighborRoamInfo->neighborRoamState)
        {
            csrNeighborRoamRequestHandoff(pMac);
        }
        else
        {
            smsLog(pMac, LOGE, FL("Non-11R Reassoc indication received in unexpected state %d"), pNeighborRoamInfo->neighborRoamState);
            VOS_ASSERT(0);
        }
    }
