#ifdef WPA_SUPPLICANT_SUPPORT
if (((pAd->StaCfg.WpaSupplicantUP)&&
             (pAd->StaCfg.WepStatus == Ndis802_11WEPEnabled)&&
             (pAd->StaCfg.PortSecured == WPA_802_1X_PORT_SECURED)) ||
            ((pAd->StaCfg.WpaSupplicantUP == WPA_SUPPLICANT_DISABLE)&&
              (pAd->StaCfg.WepStatus == Ndis802_11WEPEnabled)))
#else
		if (pAd->StaCfg.WepStatus == Ndis802_11WEPEnabled)
#endif // WPA_SUPPLICANT_SUPPORT //
		{
			PUCHAR	Key;
			UCHAR	CipherAlg;

			for (idx=0; idx < SHARE_KEY_NUM; idx++)
		{
				CipherAlg = pAd->SharedKey[BSS0][idx].CipherAlg;
			Key = pAd->SharedKey[BSS0][idx].Key;

				if (pAd->SharedKey[BSS0][idx].KeyLen > 0)
				{
					// Set key material and cipherAlg to Asic
				AsicAddSharedKeyEntry(pAd, BSS0, idx, CipherAlg, Key, NULL, NULL);

					if (idx == pAd->StaCfg.DefaultKeyId)
					{
						// Assign group key info
						RTMPAddWcidAttributeEntry(pAd, BSS0, idx, CipherAlg, NULL);

						pEntry->Aid = BSSID_WCID;
						// Assign pairwise key info
						RTMPAddWcidAttributeEntry(pAd, BSS0, idx, CipherAlg, pEntry);
					}
				}
			}
		}
