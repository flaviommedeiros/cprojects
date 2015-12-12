if (INFRA_ON(pAd) &&
		(PowerMode != Ndis802_11PowerModeCAM) &&
		(pAd->StaCfg.Psm == PWR_ACTIVE) &&
#ifdef RT2860
		RTMP_TEST_PSFLAG(pAd, fRTMP_PS_CAN_GO_SLEEP))
#else
		(pAd->Mlme.CntlMachine.CurrState == CNTL_IDLE)
