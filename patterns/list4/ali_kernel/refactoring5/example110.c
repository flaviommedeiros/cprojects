#ifdef QOS_DLS_SUPPORT
if (bDLSFrame)
		{
			COPY_MAC_ADDR(pHeader80211->Addr1, pTxBlk->pSrcBufHeader);
			COPY_MAC_ADDR(pHeader80211->Addr3, pAd->CommonCfg.Bssid);
			pHeader80211->FC.ToDs = 0;
		}
		else
#endif // QOS_DLS_SUPPORT //
		if (ADHOC_ON(pAd))
			COPY_MAC_ADDR(pHeader80211->Addr3, pAd->CommonCfg.Bssid);
		else
		COPY_MAC_ADDR(pHeader80211->Addr3, pTxBlk->pSrcBufHeader);
