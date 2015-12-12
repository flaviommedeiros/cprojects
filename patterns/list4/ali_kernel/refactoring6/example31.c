if ((bWmmCapable == 1)
#ifdef RT2870
		&& (pAd->NumberOfPipes >= 5)
#endif // RT2870 //
		)
		pAd->CommonCfg.bWmmCapable = TRUE;
	else if (bWmmCapable == 0)
		pAd->CommonCfg.bWmmCapable = FALSE;
	else
		return FALSE;
