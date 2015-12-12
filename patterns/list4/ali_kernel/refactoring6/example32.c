if ((pAd->CommonCfg.PhyMode >= PHY_11ABGN_MIXED) &&
#ifdef RT2860
				!pAd->StaCfg.AdhocBOnlyJoined &&
				!pAd->StaCfg.AdhocBGJoined &&
				(pAd->StaActive.SupportedPhyInfo.MCSSet[0] == 0xff) &&
				((pAd->StaActive.SupportedPhyInfo.MCSSet[1] == 0x00) || (pAd->Antenna.field.TxPath == 1)))
#endif
#ifdef RT2870
				(pEntry->HTCapability.MCSSet[0] == 0xff) &&
				((pEntry->HTCapability.MCSSet[1] == 0x00) || (pAd->Antenna.field.TxPath == 1))
