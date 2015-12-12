switch(pNeighborRoamInfo->neighborRoamState)
        {
            case eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN:
                if (tempVal)
                {
                    /*
                     * Since there are non-zero candidates found
                     * after the scan, reset the refresh period
                     * to minimum.
                     */
                    pNeighborRoamInfo->currentScanResultsRefreshPeriod = 
                        NEIGHBOR_SCAN_RESULTS_REFRESH_PERIOD_MIN;
#ifdef WLAN_FEATURE_VOWIFI_11R
                    /* If this is a non-11r association, then we can register the reassoc callback here as we have some 
                                        APs in the roamable AP list */
                    if (pNeighborRoamInfo->is11rAssoc)
                    {
                        /* Valid APs are found after scan. Now we can initiate pre-authentication */
                        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN)
                    }
                    else
#endif
#ifdef FEATURE_WLAN_CCX
                    /* If this is a non-11r association, then we can register the reassoc callback here as we have some 
                                        APs in the roamable AP list */
                    if (pNeighborRoamInfo->isCCXAssoc)
                    {
                        /* Valid APs are found after scan. Now we can initiate pre-authentication */
                        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN)
                    }
                    else
#endif
#ifdef FEATURE_WLAN_LFR
                    /* If LFR is enabled, then we can register the reassoc callback here as we have some 
                                        APs in the roamable AP list */
                    if (csrRoamIsFastRoamEnabled(pMac))
                    {
                        /* Valid APs are found after scan. Now we can initiate pre-authentication */
                        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN)
                    }
                    else
#endif
                    {
                       
                        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Completed scanning of CFG CHAN LIST in non-11r association. Registering reassoc callback"));
                        /* Nothing much to do now. Will continue to remain in this state in case of non-11r association */
                        /* Stop the timer. But how long the roamable AP list will be valid in here. At some point of time, we 
                           need to restart the CFG CHAN list scan procedure if reassoc callback is not invoked from TL 
                           within certain duration */
                        
//                        palTimerStop(pMac->hHdd, pNeighborRoamInfo->neighborScanTimer);
                    }
                }
                else
                {
                    NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("No candidate found after scanning in state %d.. "), pNeighborRoamInfo->neighborRoamState);
                    /* Handle it appropriately */
                    csrNeighborRoamHandleEmptyScanResult(pMac);
                }
                break;
#ifdef WLAN_FEATURE_VOWIFI_11R                
            case eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN:
                if (!tempVal)
                {
                    smsLog(pMac, LOGE, FL("No candidate found after scanning in state %d.. "), pNeighborRoamInfo->neighborRoamState);
                    /* Stop the timer here as the same timer will be started again in CFG_CHAN_SCAN_STATE */
                    csrNeighborRoamTransitToCFGChanScan(pMac);
                }
                break;
#endif /* WLAN_FEATURE_VOWIFI_11R */
            default:
                // Can come only in INIT state. Where in we are associated, we sent scan and user
                // in the meantime decides to disassoc, we will be in init state and still received call
                // back issued. Should not come here in any other state, printing just in case
                VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO, 
                        "%s: [INFOLOG] State %d\n", __func__, (pNeighborRoamInfo->neighborRoamState));

                // Lets just exit out silently.
                return eHAL_STATUS_SUCCESS;
        }
