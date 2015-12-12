#ifdef ANT_DIVERSITY_SUPPORT
if ((pAd->NicConfig2.field.AntDiversity) && (pAd->CommonCfg.bRxAntDiversity == ANT_DIVERSITY_ENABLE))
	{
		// two antenna selection mechanism- one is antenna diversity, the other is failed antenna remove
		// one is antenna diversity:there is only one antenna can rx and tx
		// the other is failed antenna remove:two physical antenna can rx and tx
			DBGPRINT(RT_DEBUG_TRACE,("AntDiv - before evaluate Pair1-Ant (%d,%d)\n",
				pAd->RxAnt.Pair1PrimaryRxAnt, pAd->RxAnt.Pair1SecondaryRxAnt));

			AsicSetRxAnt(pAd, pAd->RxAnt.Pair1SecondaryRxAnt);

			pAd->RxAnt.EvaluatePeriod = 1; // 1:Means switch to SecondaryRxAnt, 0:Means switch to Pair1PrimaryRxAnt
			pAd->RxAnt.FirstPktArrivedWhenEvaluate = FALSE;
			pAd->RxAnt.RcvPktNumWhenEvaluate = 0;

			// a one-shot timer to end the evalution
			// dynamic adjust antenna evaluation period according to the traffic
			if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_MEDIA_STATE_CONNECTED))
				RTMPSetTimer(&pAd->Mlme.RxAntEvalTimer, 100);
			else
				RTMPSetTimer(&pAd->Mlme.RxAntEvalTimer, 300);
		}
		else
#endif // ANT_DIVERSITY_SUPPORT //
	{
#ifdef CONFIG_STA_SUPPORT
		IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
		{

			if (pAd->StaCfg.Psm == PWR_SAVE)
				return;

			RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BBPR3);
			BBPR3 &= (~0x18);
			if(pAd->Antenna.field.RxPath == 3)
			{
				BBPR3 |= (0x10);
			}
			else if(pAd->Antenna.field.RxPath == 2)
			{
				BBPR3 |= (0x8);
			}
			else if(pAd->Antenna.field.RxPath == 1)
			{
				BBPR3 |= (0x0);
			}
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BBPR3);
#ifdef RTMP_MAC_PCI
			IF_DEV_CONFIG_OPMODE_ON_STA(pAd)
			pAd->StaCfg.BBPR3 = BBPR3;
#endif // RTMP_MAC_PCI //
			if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_MEDIA_STATE_CONNECTED)
			)
			{
				ULONG	TxTotalCnt = pAd->RalinkCounters.OneSecTxNoRetryOkCount +
									pAd->RalinkCounters.OneSecTxRetryOkCount +
									pAd->RalinkCounters.OneSecTxFailCount;

				// dynamic adjust antenna evaluation period according to the traffic
				if (TxTotalCnt > 50)
				{
					RTMPSetTimer(&pAd->Mlme.RxAntEvalTimer, 20);
					pAd->Mlme.bLowThroughput = FALSE;
				}
				else
				{
					RTMPSetTimer(&pAd->Mlme.RxAntEvalTimer, 300);
					pAd->Mlme.bLowThroughput = TRUE;
				}
			}
		}
#endif // CONFIG_STA_SUPPORT //
	}
