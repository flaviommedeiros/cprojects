if ((psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE)
#ifdef WLAN_SOFTAP_FEATURE
                      || (psessionEntry->limSystemRole == eLIM_AP_ROLE)
#endif                   
                    ){
                        limProcessAssocReqFrame(pMac, pRxPacketInfo, LIM_REASSOC, psessionEntry);
                    }
                    else
                    {
                        // Unwanted messages - Log error
                        limLog(pMac, LOGE, FL("unexpected message received %X\n"),limMsg->type);
                        limPrintMsgName(pMac, LOGE, limMsg->type);
                    }
