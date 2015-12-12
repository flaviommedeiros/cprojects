#ifdef RT2860
if (!RTMP_TEST_PSFLAG(pAd, fRTMP_PS_DISABLE_TX))
#endif
		HAL_KickOutTx(pAd, pTxBlk, pTxBlk->QueIdx);
