if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE) ||
#ifdef RTMP_MAC_PCI
	    (pAd->bPCIclkOff == TRUE) ||
#endif /* RTMP_MAC_PCI // */
	    RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF) ||
	    RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BSS_SCAN_IN_PROGRESS))
		return;