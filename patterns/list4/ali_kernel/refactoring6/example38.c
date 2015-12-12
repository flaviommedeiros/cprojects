if (((pAd->CommonCfg.bIEEE80211H == 1) &&
            (pAd->MlmeAux.Channel > 14) &&
             RadarChannelCheck(pAd, pAd->MlmeAux.Channel))
#ifdef CARRIER_DETECTION_SUPPORT // Roger sync Carrier
             || (pAd->CommonCfg.CarrierDetect.Enable == TRUE)
#endif // CARRIER_DETECTION_SUPPORT //
            )
		{
			//
			// We can't send any Probe request frame to meet 802.11h.
			//
			if (pBss->Hidden == 0)
			break;
		}
