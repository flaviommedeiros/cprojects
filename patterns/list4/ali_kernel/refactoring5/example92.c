#ifdef RT30xx
if (pAd->NicConfig2.field.AntDiversity)
		{
			if ((pAd->RxAnt.RcvPktNumWhenEvaluate != 0) && (pAd->RxAnt.Pair1AvgRssi[pAd->RxAnt.Pair1SecondaryRxAnt] >= pAd->RxAnt.Pair1AvgRssi[pAd->RxAnt.Pair1PrimaryRxAnt]))
			{
				UCHAR			temp;

				//
				// select PrimaryRxAntPair
				//    Role change, Used Pair1SecondaryRxAnt as PrimaryRxAntPair.
				//    Since Pair1SecondaryRxAnt Quality good than Pair1PrimaryRxAnt
				//
				temp = pAd->RxAnt.Pair1PrimaryRxAnt;
				pAd->RxAnt.Pair1PrimaryRxAnt = pAd->RxAnt.Pair1SecondaryRxAnt;
				pAd->RxAnt.Pair1SecondaryRxAnt = temp;

				pAd->RxAnt.Pair1LastAvgRssi = (pAd->RxAnt.Pair1AvgRssi[pAd->RxAnt.Pair1SecondaryRxAnt] >> 3);
				pAd->RxAnt.EvaluateStableCnt = 0;
			}
			else
			{
				// if the evaluated antenna is not better than original, switch back to original antenna
				AsicSetRxAnt(pAd, pAd->RxAnt.Pair1PrimaryRxAnt);
				pAd->RxAnt.EvaluateStableCnt ++;
			}

			pAd->RxAnt.EvaluatePeriod = 0; // 1:Means switch to SecondaryRxAnt, 0:Means switch to Pair1PrimaryRxAnt

			DBGPRINT(RT_DEBUG_TRACE,("AsicRxAntEvalAction::After Eval(fix in #%d), <%d, %d>, RcvPktNumWhenEvaluate=%ld\n",
					pAd->RxAnt.Pair1PrimaryRxAnt, (pAd->RxAnt.Pair1AvgRssi[0] >> 3), (pAd->RxAnt.Pair1AvgRssi[1] >> 3), pAd->RxAnt.RcvPktNumWhenEvaluate));
		}
		else
#endif
		{
			if (pAd->StaCfg.Psm == PWR_SAVE)
				return;

			// if the traffic is low, use average rssi as the criteria
			if (pAd->Mlme.bLowThroughput == TRUE)
			{
				rssi0 = pAd->StaCfg.RssiSample.LastRssi0;
				rssi1 = pAd->StaCfg.RssiSample.LastRssi1;
				rssi2 = pAd->StaCfg.RssiSample.LastRssi2;
			}
			else
			{
				rssi0 = pAd->StaCfg.RssiSample.AvgRssi0;
				rssi1 = pAd->StaCfg.RssiSample.AvgRssi1;
				rssi2 = pAd->StaCfg.RssiSample.AvgRssi2;
			}

			if(pAd->Antenna.field.RxPath == 3)
			{
				larger = max(rssi0, rssi1);

				if (larger > (rssi2 + 20))
					pAd->Mlme.RealRxPath = 2;
				else
					pAd->Mlme.RealRxPath = 3;
			}
			else if(pAd->Antenna.field.RxPath == 2)
			{
				if (rssi0 > (rssi1 + 20))
					pAd->Mlme.RealRxPath = 1;
				else
					pAd->Mlme.RealRxPath = 2;
			}

			RTMP_BBP_IO_READ8_BY_REG_ID(pAd, BBP_R3, &BBPR3);
			BBPR3 &= (~0x18);
			if(pAd->Mlme.RealRxPath == 3)
			{
				BBPR3 |= (0x10);
			}
			else if(pAd->Mlme.RealRxPath == 2)
			{
				BBPR3 |= (0x8);
			}
			else if(pAd->Mlme.RealRxPath == 1)
			{
				BBPR3 |= (0x0);
			}
			RTMP_BBP_IO_WRITE8_BY_REG_ID(pAd, BBP_R3, BBPR3);
#ifdef RT2860
			pAd->StaCfg.BBPR3 = BBPR3;
#endif
		}
