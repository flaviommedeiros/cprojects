#ifdef WLAN_FEATURE_11AC
if (WDI_getFwWlanFeatCaps(DOT11AC))
    WDI_CopyWDIConfigBSSToHALConfigBSS( (tConfigBssParams*)&halConfigBssReqMsg.uBssParams.configBssParams_V1,
                                        &pwdiConfigBSSParams->wdiReqInfo);
  else
#endif
  WDI_CopyWDIConfigBSSToHALConfigBSS( &halConfigBssReqMsg.uBssParams.configBssParams,
                                      &pwdiConfigBSSParams->wdiReqInfo);
