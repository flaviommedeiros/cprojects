#if !defined WLAN_FEATURE_VOWIFI
if( !limGetHTCapability( pMac, eHT_SUPPORTED_CHANNEL_WIDTH_SET, psessionEntry ))
#else
   if( !limGetHTCapability( pMac, eHT_SUPPORTED_CHANNEL_WIDTH_SET ))
#endif
        return;
