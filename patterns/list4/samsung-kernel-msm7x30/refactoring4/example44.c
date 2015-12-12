#ifdef WLAN_SOFTAP_FEATURE
if (psessionEntry->gLimOverlapHt20Params.numSta &&
                          !psessionEntry->gLimOverlapHt20Params.protectionEnabled)
#else
                      limUpdateOverlapStaParam(pMac, pMh->bssId, &(pMac->lim.gLimOverlapHt20Params));
