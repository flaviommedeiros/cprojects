#ifdef WPA_SUPPLICANT_SUPPORT
if (pAd->StaCfg.WpaSupplicantUP)
		{
			WpaSendMicFailureToWpaSupplicant(pAd, (pWpaKey->Type == PAIRWISEKEY) ? TRUE : FALSE);
		}
		else
#endif // WPA_SUPPLICANT_SUPPORT //
		{
			RTMPReportMicError(pAd, pWpaKey);
		}
