#ifdef WLAN_SOFTAP_FEATURE
if (psessionEntry->gLimOverlap11gParams.numSta &&
                              !psessionEntry->gLimOverlap11gParams.protectionEnabled)
#else
                          limUpdateOverlapStaParam(pMac, pMh->bssId, &(pMac->lim.gLimOverlap11gParams));
