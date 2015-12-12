#ifdef RT3090
if(IS_RT3090A(pAd))
	pAd->CommonCfg.CarrierDetect.threshold = CARRIER_DETECT_THRESHOLD_3090A;
	else
#endif // RT3090 //
	pAd->CommonCfg.CarrierDetect.threshold = CARRIER_DETECT_THRESHOLD;
