#ifdef NDIS51_MINIPORT
if (pAd->StaCfg.WindowsPowerProfile == NdisPowerProfileBattery)
		PowerMode = pAd->StaCfg.WindowsBatteryPowerMode;
	else
#endif
		PowerMode = pAd->StaCfg.WindowsPowerMode;
