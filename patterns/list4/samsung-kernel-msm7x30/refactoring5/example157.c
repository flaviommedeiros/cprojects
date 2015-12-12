#ifdef WLAN_SOFTAP_FEATURE
if ((psessionEntry->limSystemRole == eLIM_AP_ROLE ) &&
                     !psessionEntry->gLimNoShortSlotParams.staNoShortSlotCache[i].active)
                    break;
                 else
#endif
                 {
                     if (!pMac->lim.gLimNoShortSlotParams.staNoShortSlotCache[i].active)
                          break;
                 }
