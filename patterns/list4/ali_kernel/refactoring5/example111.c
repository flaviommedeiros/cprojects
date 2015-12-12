#ifdef SIOCSIWGENIE
if ((pAd->StaCfg.WpaSupplicantUP == WPA_SUPPLICANT_ENABLE) &&
				(pAd->StaCfg.bRSN_IE_FromWpaSupplicant == TRUE))
			{
				MakeOutgoingFrame(pOutBuffer + FrameLen,		&tmp,
						pAd->StaCfg.RSNIE_Len,			pAd->StaCfg.RSN_IE,
						END_OF_ARGS);
			}
			else
#endif
#endif // NATIVE_WPA_SUPPLICANT_SUPPORT //
			{
			MakeOutgoingFrame(pOutBuffer + FrameLen,		&tmp,
						1,                              &RSNIe,
					1,                              &pAd->StaCfg.RSNIE_Len,
					pAd->StaCfg.RSNIE_Len,			pAd->StaCfg.RSN_IE,
					END_OF_ARGS);
			}
