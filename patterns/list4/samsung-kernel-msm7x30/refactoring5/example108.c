#ifdef WLAN_FEATURE_11AC
if(cfgCb > 2 )
    {
	if(!WDA_getFwWlanFeatCaps(DOT11AC)) {
            cfgCb = csrGetHTCBStateFromVHTCBState(cfgCb);
	}
	else 
	{
            ccmCfgSetInt(pMac, WNI_CFG_VHT_CHANNEL_WIDTH,  pMac->roam.configParam.nVhtChannelWidth, NULL, eANI_BOOLEAN_FALSE);
	}
    }
    else
#endif
    ccmCfgSetInt(pMac, WNI_CFG_CHANNEL_BONDING_MODE, cfgCb, NULL, eANI_BOOLEAN_FALSE);
