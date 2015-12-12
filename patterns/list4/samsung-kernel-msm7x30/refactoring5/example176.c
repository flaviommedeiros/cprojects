#ifdef WLAN_FEATURE_11AC
if ( peSession->vhtCapability )
    {
        limSendSwitchChnlParams( pMac, channel, limGet11ACPhyCBState( pMac,channel,secChannelOffset ), maxTxPower, peSessionId);
    }
    else
#endif
    {
        limSendSwitchChnlParams( pMac, channel, secChannelOffset, maxTxPower, peSessionId);
    }
