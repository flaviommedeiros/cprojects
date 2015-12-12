if ((pAd->CommonCfg.PhyMode == PHY_11ABG_MIXED)
#ifdef DOT11_N_SUPPORT
				|| (pAd->CommonCfg.PhyMode == PHY_11ABGN_MIXED) || (pAd->CommonCfg.PhyMode == PHY_11AGN_MIXED)
#endif // DOT11_N_SUPPORT //
			)
			{
				if (pAd->MlmeAux.Channel > 14)
					RTMPSetTimer(&pAd->MlmeAux.ScanTimer, ScanTimeIn5gChannel);
				else
				RTMPSetTimer(&pAd->MlmeAux.ScanTimer, MIN_CHANNEL_TIME);
			}
			else
				RTMPSetTimer(&pAd->MlmeAux.ScanTimer, MAX_CHANNEL_TIME);
