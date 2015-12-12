if ((pEntry->RateLen == 4 || pAd->CommonCfg.PhyMode==PHY_11B)
#ifdef DOT11_N_SUPPORT
		//Iverson mark for Adhoc b mode,sta will use rate 54  Mbps when connect with sta b/g/n mode
		/* && (pEntry->HTCapability.MCSSet[0] == 0) && (pEntry->HTCapability.MCSSet[1] == 0)*/
#endif // DOT11_N_SUPPORT //
			)
		{// B only AP
			*ppTable = RateSwitchTable11B;
			*pTableSize = RateSwitchTable11B[0];
			*pInitTxRateIdx = RateSwitchTable11B[1];

			break;
		}
