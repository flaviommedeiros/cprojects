#ifdef QOS_DLS_SUPPORT
if (bDLSFrame)
			{
				COPY_MAC_ADDR(pHeader_802_11->Addr1, pTxBlk->pSrcBufHeader);
				COPY_MAC_ADDR(pHeader_802_11->Addr2, pAd->CurrentAddress);
				COPY_MAC_ADDR(pHeader_802_11->Addr3, pAd->CommonCfg.Bssid);
				pHeader_802_11->FC.ToDs = 0;
			}
			else
#endif // QOS_DLS_SUPPORT //
			{
			COPY_MAC_ADDR(pHeader_802_11->Addr1, pAd->CommonCfg.Bssid);
			COPY_MAC_ADDR(pHeader_802_11->Addr2, pAd->CurrentAddress);
			COPY_MAC_ADDR(pHeader_802_11->Addr3, pTxBlk->pSrcBufHeader);
			pHeader_802_11->FC.ToDs = 1;
		}
