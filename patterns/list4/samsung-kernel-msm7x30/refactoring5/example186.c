#ifdef WLAN_FEATURE_11AC
if (WDI_getFwWlanFeatCaps(DOT11AC))
	  halMsgHeader.msgVersion = WLAN_HAL_MSG_VERSION1;
  else
#endif
	  halMsgHeader.msgVersion = WLAN_HAL_MSG_VERSION0;
