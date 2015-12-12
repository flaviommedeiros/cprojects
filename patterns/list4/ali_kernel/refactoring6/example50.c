if (((pAd->CommonCfg.bIEEE80211H == 1) &&
            (pAd->MlmeAux.Channel > 14) &&
             RadarChannelCheck(pAd, pInBss->Channel))
#ifdef CARRIER_DETECTION_SUPPORT // Roger sync Carrier
             || (pAd->CommonCfg.CarrierDetect.Enable == TRUE)
#endif // CARRIER_DETECTION_SUPPORT //
            )
{
			if (pInBss->Hidden)
				bIsHiddenApIncluded = TRUE;
}
