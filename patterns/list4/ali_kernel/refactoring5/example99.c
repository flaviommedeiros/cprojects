#ifdef DOT11_N_SUPPORT
if (pAd->CommonCfg.PhyMode >= PHY_11ABGN_MIXED)
		{
			RTMPUpdateHTIE(&pAd->CommonCfg.DesiredHtPhy, &pAd->StaCfg.DesiredHtPhyInfo.MCSSet[0], &pAd->MlmeAux.HtCapability, &pAd->MlmeAux.AddHtInfo);
			pAd->MlmeAux.HtCapabilityLen = sizeof(HT_CAPABILITY_IE);
			// Not turn pAd->StaActive.SupportedHtPhy.bHtEnable = TRUE here.
			DBGPRINT(RT_DEBUG_TRACE, ("SYNC -pAd->StaActive.SupportedHtPhy.bHtEnable = TRUE\n"));
		}
		else
#endif // DOT11_N_SUPPORT //
		{
			pAd->MlmeAux.HtCapabilityLen = 0;
			pAd->StaActive.SupportedPhyInfo.bHtEnable = FALSE;
			NdisZeroMemory(&pAd->StaActive.SupportedPhyInfo.MCSSet[0], 16);
		}
