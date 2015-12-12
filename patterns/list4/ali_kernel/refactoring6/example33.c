if ((pAd->CommonCfg.PhyMode >= PHY_11ABGN_MIXED) &&
#ifdef RT2860
					!pAd->StaCfg.AdhocBOnlyJoined &&
					!pAd->StaCfg.AdhocBGJoined &&
					(pAd->StaActive.SupportedPhyInfo.MCSSet[0] == 0xff) &&
					(pAd->StaActive.SupportedPhyInfo.MCSSet[1] == 0xff) &&
#endif
#ifdef RT2870
					(pEntry->HTCapability.MCSSet[0] == 0xff) &&
					(pEntry->HTCapability.MCSSet[1] == 0xff) &&
#endif
					(pAd->Antenna.field.TxPath == 2))
			{// 11N 2S Adhoc
				if (pAd->LatchRfRegs.Channel <= 14)
				{
					*ppTable = RateSwitchTable11N2S;
					*pTableSize = RateSwitchTable11N2S[0];
					*pInitTxRateIdx = RateSwitchTable11N2S[1];
				}
				else
				{
					*ppTable = RateSwitchTable11N2SForABand;
					*pTableSize = RateSwitchTable11N2SForABand[0];
					*pInitTxRateIdx = RateSwitchTable11N2SForABand[1];
				}

			}
			else
#ifdef RT2860
				if (pAd->CommonCfg.PhyMode == PHY_11B)
			{
				*ppTable = RateSwitchTable11B;
				*pTableSize = RateSwitchTable11B[0];
				*pInitTxRateIdx = RateSwitchTable11B[1];

			}
	        else if((pAd->LatchRfRegs.Channel <= 14) && (pAd->StaCfg.AdhocBOnlyJoined == TRUE))
#endif
#ifdef RT2870
				if ((pEntry->RateLen == 4)
					&& (pEntry->HTCapability.MCSSet[0] == 0) && (pEntry->HTCapability.MCSSet[1] == 0)
					)
#endif
			{
				// USe B Table when Only b-only Station in my IBSS .
				*ppTable = RateSwitchTable11B;
				*pTableSize = RateSwitchTable11B[0];
				*pInitTxRateIdx = RateSwitchTable11B[1];

			}
			else if (pAd->LatchRfRegs.Channel <= 14)
			{
				*ppTable = RateSwitchTable11BG;
				*pTableSize = RateSwitchTable11BG[0];
				*pInitTxRateIdx = RateSwitchTable11BG[1];

			}
			else
			{
				*ppTable = RateSwitchTable11G;
				*pTableSize = RateSwitchTable11G[0];
				*pInitTxRateIdx = RateSwitchTable11G[1];

			}
