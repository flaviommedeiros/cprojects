#ifdef WPA_SUPPLICANT_SUPPORT
if (pAd->StaCfg.WpaSupplicantUP &&
			(pAd->StaCfg.WepStatus == Ndis802_11WEPEnabled) &&
			(pAd->StaCfg.IEEE8021X == TRUE))
			;
		else
#endif // WPA_SUPPLICANT_SUPPORT //
		{
			pAd->StaCfg.PortSecured = WPA_802_1X_PORT_SECURED;
			pAd->StaCfg.PrivacyFilter = Ndis802_11PrivFilterAcceptAll;
		}
