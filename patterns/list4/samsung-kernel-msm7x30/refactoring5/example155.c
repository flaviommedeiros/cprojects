#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE){
                    limLog(pMac, LOGE, FL("No space in Short cache (#active %d, #sta %d) for sta "),
                            i, psessionEntry->gLimNoShortParams.numNonShortPreambleSta);
                    limPrintMacAddr(pMac, peerMacAddr, LOGE);
                    return;
                }
                else
#endif
                {
                    limLog(pMac, LOGE, FL("No space in Short cache (#active %d, #sta %d) for sta "),
                            i, pMac->lim.gLimNoShortParams.numNonShortPreambleSta);
                    limPrintMacAddr(pMac, peerMacAddr, LOGE);
                    return;
                }
