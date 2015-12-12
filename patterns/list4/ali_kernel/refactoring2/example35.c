#ifdef NATIVE_WPA_SUPPLICANT_SUPPORT
if ((pAd->StaCfg.WpaSupplicantUP != WPA_SUPPLICANT_ENABLE) &&
				(pAd->StaCfg.bRSN_IE_FromWpaSupplicant == FALSE))
#endif // SIOCSIWGENIE //
#endif // NATIVE_WPA_SUPPLICANT_SUPPORT //
            RTMPMakeRSNIE(pAd, pAd->StaCfg.AuthMode, pAd->StaCfg.WepStatus, BSS0);
