#ifdef QOS_DLS_SUPPORT
if (pAd->MacTab.Content[pInfo->Wcid].ValidAsDls)
				ActHeaderInit(pAd, &Frame.Hdr, pInfo->pAddr, pAd->CurrentAddress, pAd->CommonCfg.Bssid);
			else
#endif // QOS_DLS_SUPPORT //
			ActHeaderInit(pAd, &Frame.Hdr, pAd->CommonCfg.Bssid, pAd->CurrentAddress, pInfo->pAddr);
