#ifdef CONFIG_STA_SUPPORT
if (pAd->Mlme.OneSecPeriodicRound % 2 == 1)
#endif // CONFIG_STA_SUPPORT //
	{
		// patch for AsicSetRxAnt failed
		pAd->RxAnt.EvaluatePeriod = 0;

		// check every 2 second. If rcv-beacon less than 5 in the past 2 second, then AvgRSSI is no longer a
		// valid indication of the distance between this AP and its clients.
		if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_MEDIA_STATE_CONNECTED))
		{
			SHORT	realavgrssi1;

			// if no traffic then reset average rssi to trigger evaluation
#ifdef CONFIG_STA_SUPPORT
			if (pAd->StaCfg.NumOfAvgRssiSample < 5)
			{
				pAd->RxAnt.Pair1LastAvgRssi = (-99);
				pAd->RxAnt.Pair2LastAvgRssi = (-99);
				DBGPRINT(RT_DEBUG_TRACE, ("MlmePeriodicExec: no traffic/beacon, reset RSSI\n"));
			}

			pAd->StaCfg.NumOfAvgRssiSample = 0;
			realavgrssi1 = (pAd->RxAnt.Pair1AvgRssi[pAd->RxAnt.Pair1PrimaryRxAnt] >> 3);
#endif // CONFIG_STA_SUPPORT //

			DBGPRINT(RT_DEBUG_TRACE,("Ant-realrssi0(%d), Lastrssi0(%d), EvaluateStableCnt=%d\n", realavgrssi1, pAd->RxAnt.Pair1LastAvgRssi, pAd->RxAnt.EvaluateStableCnt));

			// if the difference between two rssi is larger or less than 5, then evaluate the other antenna
			if ((pAd->RxAnt.EvaluateStableCnt < 2) || (realavgrssi1 > (pAd->RxAnt.Pair1LastAvgRssi + 5)) || (realavgrssi1 < (pAd->RxAnt.Pair1LastAvgRssi - 5)))
				AsicEvaluateRxAnt(pAd);

				pAd->RxAnt.Pair1LastAvgRssi = realavgrssi1;
		}
		else
		{
			// if not connected, always switch antenna to try to connect
			UCHAR	temp;

			temp = pAd->RxAnt.Pair1PrimaryRxAnt;
			pAd->RxAnt.Pair1PrimaryRxAnt = pAd->RxAnt.Pair1SecondaryRxAnt;
			pAd->RxAnt.Pair1SecondaryRxAnt = temp;

			DBGPRINT(RT_DEBUG_TRACE, ("MlmePeriodicExec: no connect, switch to another one to try connection\n"));

			AsicSetRxAnt(pAd, pAd->RxAnt.Pair1PrimaryRxAnt);
		}
	}
