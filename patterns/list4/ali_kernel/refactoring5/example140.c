#ifdef CONFIG_STA_SUPPORT
if ((INFRA_ON(pAd)) && (pAd->OpMode == OPMODE_STA)) // must be unicast to AP
		return TRUE;
	else
#endif // CONFIG_STA_SUPPORT //
		return FALSE;
