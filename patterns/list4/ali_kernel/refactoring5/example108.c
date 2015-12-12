#ifdef QOS_DLS_SUPPORT
if (RX_BLK_TEST_FLAG(pRxBlk, fRX_DLS))
		{
			MAC_TABLE_ENTRY *pDlsEntry = NULL;

			pDlsEntry = DlsEntryTableLookupByWcid(pAd, pRxWI->WirelessCliID, pHeader->Addr2, TRUE);
										                        if(pDlsEntry)
			Update_Rssi_Sample(pAd, &pDlsEntry->RssiSample, pRxWI);
		}
		else
#endif // QOS_DLS_SUPPORT //
		if (ADHOC_ON(pAd))
		{
			pEntry = MacTableLookup(pAd, pHeader->Addr2);
			if (pEntry)
				Update_Rssi_Sample(pAd, &pEntry->RssiSample, pRxWI);
		}
