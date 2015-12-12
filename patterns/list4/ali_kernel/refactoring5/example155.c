#ifdef QOS_DLS_SUPPORT
if (pAd->MacTab.Content[Elem->Wcid].ValidAsDls)
			ActHeaderInit(pAd, &ADDframe.Hdr, pAddr, pAd->CurrentAddress, pAd->CommonCfg.Bssid);
		else
#endif // QOS_DLS_SUPPORT //
		ActHeaderInit(pAd, &ADDframe.Hdr, pAd->CommonCfg.Bssid, pAd->CurrentAddress, pAddr);
