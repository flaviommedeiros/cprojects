if ((pAd->CommonCfg.BACapability.field.AutoBA == TRUE)&&
#ifdef RT2860
        (pAd->StaActive.SupportedPhyInfo.bHtEnable == TRUE))
#endif
#ifdef RT2870
        IS_HT_STA(pEntry)
