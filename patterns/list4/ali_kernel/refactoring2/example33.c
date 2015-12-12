#ifdef WPA_SUPPLICANT_SUPPORT
if (pAd->StaCfg.WpaSupplicantUP != WPA_SUPPLICANT_ENABLE_WITH_WEB_UI)
#endif // WPA_SUPPLICANT_SUPPORT //
            {
			// Set the AutoReconnectSsid to prevent it reconnect to old SSID
			// Since calling this indicate user don't want to connect to that SSID anymore.
			pAd->MlmeAux.AutoReconnectSsidLen= 32;
			NdisZeroMemory(pAd->MlmeAux.AutoReconnectSsid, pAd->MlmeAux.AutoReconnectSsidLen);
            }
