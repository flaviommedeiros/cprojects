if ((pFrame->StatusCode == 37)
#ifdef CONFIG_STA_SUPPORT
            || ((pAd->OpMode == OPMODE_STA) && STA_TGN_WIFI_ON(pAd) && (pFrame->StatusCode != 0))
#endif // CONFIG_STA_SUPPORT //
            )
		{
			pAd->MacTab.Content[Elem->Wcid].BADeclineBitmap |= 1<<pFrame->BaParm.TID;
		}
