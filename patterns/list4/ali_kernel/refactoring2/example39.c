#ifdef WPA_SUPPLICANT_SUPPORT
if (pAd->StaCfg.WpaSupplicantUP == WPA_SUPPLICANT_DISABLE)
#endif // WPA_SUPPLICANT_SUPPORT //
    {
	// WPA MIC error should block association attempt for 60 seconds
		if (pAd->StaCfg.bBlockAssoc &&
			RTMP_TIME_AFTER(pAd->Mlme.Now32, pAd->StaCfg.LastMicErrorTime + (60*OS_HZ)))
		pAd->StaCfg.bBlockAssoc = FALSE;
    }
