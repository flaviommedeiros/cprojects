if (pAd->CommonCfg.PhyMode == PHY_11ABG_MIXED
#ifdef DOT11_N_SUPPORT
			|| pAd->CommonCfg.PhyMode == PHY_11ABGN_MIXED
#endif // DOT11_N_SUPPORT //
		)
		{
			if (pAd->LatchRfRegs.Channel > 14)
				pAd->CommonCfg.MlmeTransmit.field.MODE = 1;
			else
				pAd->CommonCfg.MlmeTransmit.field.MODE = 0;
		}
