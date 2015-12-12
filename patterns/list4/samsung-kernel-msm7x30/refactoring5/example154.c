#ifdef WLAN_SOFTAP_FEATURE
if ( (psessionEntry->limSystemRole == eLIM_AP_ROLE )  &&
                      !psessionEntry->gLimNoShortParams.staNoShortCache[i].active)
                     break;
                else        
#endif        
                {
                    if (!pMac->lim.gLimNoShortParams.staNoShortCache[i].active)
                    break;
                }
