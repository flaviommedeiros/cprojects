#ifdef DOT11_N_SUPPORT
if (pTxRate->ShortGI && (pAd->StaCfg.MaxHTPhyMode.field.ShortGI))
			pAd->StaCfg.HTPhyMode.field.ShortGI = GI_400;
		else
#endif // DOT11_N_SUPPORT //
			pAd->StaCfg.HTPhyMode.field.ShortGI = GI_800;
