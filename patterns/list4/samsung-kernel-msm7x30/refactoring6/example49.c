if((eCSR_SCAN_REQUEST_FULL_SCAN == pScanRequest->requestType) ||
                        (eCSR_SCAN_P2P_DISCOVERY == pScanRequest->requestType)
#ifdef SOFTAP_CHANNEL_RANGE
                        ||(eCSR_SCAN_SOFTAP_CHANNEL_RANGE == pScanRequest->requestType)
#endif
                 )
                {
                    pScanCmd->u.scanCmd.reason = eCsrScanUserRequest;
                }
                else if(eCSR_SCAN_HO_BG_SCAN == pScanRequest->requestType)
                {
                    pScanCmd->u.scanCmd.reason = eCsrScanBgScan;
                }
                else if(eCSR_SCAN_HO_PROBE_SCAN == pScanRequest->requestType)
                {
                    pScanCmd->u.scanCmd.reason = eCsrScanProbeBss;
                }
#if defined WLAN_FEATURE_P2P
                else if(eCSR_SCAN_P2P_FIND_PEER == pScanRequest->requestType)
                {
                    pScanCmd->u.scanCmd.reason = eCsrScanP2PFindPeer;
                }
#endif                
                else
                {
                    pScanCmd->u.scanCmd.reason = eCsrScanIdleScan;
                }
