#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE){
                palCopyMemory( pMac->hHdd, psessionEntry->gLimNoShortParams.staNoShortCache[i].addr,
                        peerMacAddr,  sizeof(tSirMacAddr));
                psessionEntry->gLimNoShortParams.staNoShortCache[i].active = true;
                psessionEntry->gLimNoShortParams.numNonShortPreambleSta++;
            }else
#endif
            {
                palCopyMemory( pMac->hHdd, pMac->lim.gLimNoShortParams.staNoShortCache[i].addr,
                               peerMacAddr,  sizeof(tSirMacAddr));
                pMac->lim.gLimNoShortParams.staNoShortCache[i].active = true;
                pMac->lim.gLimNoShortParams.numNonShortPreambleSta++;        
            }
