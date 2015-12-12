#ifdef WLAN_FEATURE_11AC
if (WDI_getFwWlanFeatCaps(DOT11AC))
	  uMsgSize = sizeof(halConfigStaReqMsg.uStaParams.configStaParams_V1); // Version-1 For 11AC
  else
#endif
	  uMsgSize = sizeof(halConfigStaReqMsg.uStaParams.configStaParams);
