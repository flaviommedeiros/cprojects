#ifdef QOS_DLS_SUPPORT
if (pMacEntry &&
		(pAd->StaCfg.BssType == BSS_INFRA) &&
		(pMacEntry->ValidAsDls == TRUE))
		pTxWI->WirelessCliID = BSSID_WCID;
	else
#endif // QOS_DLS_SUPPORT //
#endif // CONFIG_STA_SUPPORT //
	pTxWI->WirelessCliID		= pTxBlk->Wcid;
