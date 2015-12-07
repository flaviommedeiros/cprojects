#ifdef RTL8192E
if(eRFPowerState == priv->ieee80211->eRFPowerState && priv->bHwRfOffAction == 0)
#else
	if(eRFPowerState == priv->ieee80211->eRFPowerState)
#endif
	{
		RT_TRACE(COMP_POWER, "<--------- SetRFPowerState(): discard the request for eRFPowerState(%d) is the same.\n", eRFPowerState);
		return bResult;
	}
