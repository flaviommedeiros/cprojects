if ((pAd->CommonCfg.PhyMode == PHY_11ABG_MIXED) ||
			(pAd->CommonCfg.PhyMode == PHY_11A))
			pAd->CommonCfg.PhyMode = PHY_11BG_MIXED;
#ifdef DOT11_N_SUPPORT
		else if ((pAd->CommonCfg.PhyMode == PHY_11ABGN_MIXED)	||
				 (pAd->CommonCfg.PhyMode == PHY_11AN_MIXED)	||
				 (pAd->CommonCfg.PhyMode == PHY_11AGN_MIXED)	||
				 (pAd->CommonCfg.PhyMode == PHY_11N_5G))
			pAd->CommonCfg.PhyMode = PHY_11BGN_MIXED;
#endif
