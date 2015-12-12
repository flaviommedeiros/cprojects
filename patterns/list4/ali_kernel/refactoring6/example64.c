if ((*pBssType == BSS_INFRA || *pBssType == BSS_ADHOC || *pBssType == BSS_ANY)
		&& (*pScanType == SCAN_ACTIVE || *pScanType == SCAN_PASSIVE
#ifdef CONFIG_STA_SUPPORT
#endif // CONFIG_STA_SUPPORT //
		))
	{
		return TRUE;
	}
	else
	{
		DBGPRINT(RT_DEBUG_TRACE, ("MlmeScanReqSanity fail - wrong BssType or ScanType\n"));
		return FALSE;
	}
