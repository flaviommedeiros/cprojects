if (((pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPA) ||
         (pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPAPSK) ||
         (pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPA2) ||
         (pAd->StaCfg.AuthMode == Ndis802_11AuthModeWPA2PSK)
#ifdef WPA_SUPPLICANT_SUPPORT
			  || (pAd->StaCfg.IEEE8021X == TRUE)
#endif
        ) &&
       (pAd->StaCfg.PortSecured == WPA_802_1X_PORT_NOT_SECURED))
	{
		return;
	}
