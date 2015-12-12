#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE){
                palCopyMemory( pMac->hHdd, psessionEntry->gLimNoShortSlotParams.staNoShortSlotCache[i].addr,
                               peerMacAddr, sizeof(tSirMacAddr));
                psessionEntry->gLimNoShortSlotParams.staNoShortSlotCache[i].active = true;
                psessionEntry->gLimNoShortSlotParams.numNonShortSlotSta++;
            }else
#endif
            {
                palCopyMemory( pMac->hHdd, pMac->lim.gLimNoShortSlotParams.staNoShortSlotCache[i].addr,
                          peerMacAddr, sizeof(tSirMacAddr));
                pMac->lim.gLimNoShortSlotParams.staNoShortSlotCache[i].active = true;
                pMac->lim.gLimNoShortSlotParams.numNonShortSlotSta++;
            }
