#ifdef DOT11_N_SUPPORT
if (!((pAd->CommonCfg.RxStream == 1)&&(pAd->CommonCfg.TxStream == 1)) &&
		(pAd->StaCfg.bForceTxBurst == FALSE) &&
		(((pAd->StaActive.SupportedPhyInfo.bHtEnable == FALSE) && OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_WMM_INUSED))
		|| ((pAd->StaActive.SupportedPhyInfo.bHtEnable == TRUE) && (pAd->CommonCfg.BACapability.field.Policy == BA_NOTUSE))))
	{
		RTMP_IO_READ32(pAd, EDCA_AC0_CFG, &Data);
		Data  &= 0xFFFFFF00;
		RTMP_IO_WRITE32(pAd, EDCA_AC0_CFG, Data);

		RTMP_IO_WRITE32(pAd, PBF_MAX_PCNT, 0x1F3F7F9F);
		DBGPRINT(RT_DEBUG_TRACE, ("Txburst 1\n"));
	}
	else
#endif // DOT11_N_SUPPORT //
	if (pAd->CommonCfg.bEnableTxBurst)
	{
		RTMP_IO_READ32(pAd, EDCA_AC0_CFG, &Data);
		Data  &= 0xFFFFFF00;
		Data  |= 0x60;
		RTMP_IO_WRITE32(pAd, EDCA_AC0_CFG, Data);
		pAd->CommonCfg.IOTestParm.bNowAtherosBurstOn = TRUE;

		RTMP_IO_WRITE32(pAd, PBF_MAX_PCNT, 0x1F3FBF9F);
		DBGPRINT(RT_DEBUG_TRACE, ("Txburst 2\n"));
	}
	else
	{
		RTMP_IO_READ32(pAd, EDCA_AC0_CFG, &Data);
		Data  &= 0xFFFFFF00;
		RTMP_IO_WRITE32(pAd, EDCA_AC0_CFG, Data);

		RTMP_IO_WRITE32(pAd, PBF_MAX_PCNT, 0x1F3F7F9F);
		DBGPRINT(RT_DEBUG_TRACE, ("Txburst 3\n"));
	}
