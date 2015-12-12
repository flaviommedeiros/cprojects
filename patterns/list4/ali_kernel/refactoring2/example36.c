#ifdef NATIVE_WPA_SUPPLICANT_SUPPORT
if ((pAd->StaCfg.WpaSupplicantUP != WPA_SUPPLICANT_ENABLE) ||
				(pAd->StaCfg.bRSN_IE_FromWpaSupplicant == FALSE))
#endif
#endif // NATIVE_WPA_SUPPLICANT_SUPPORT //
			{
            // Append Variable IE
            NdisMoveMemory(pAd->StaCfg.ReqVarIEs + VarIesOffset, &RSNIe, 1);
            VarIesOffset += 1;
            NdisMoveMemory(pAd->StaCfg.ReqVarIEs + VarIesOffset, &pAd->StaCfg.RSNIE_Len, 1);
            VarIesOffset += 1;
			}
