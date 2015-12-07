if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS |
			   fRTMP_ADAPTER_HALT_IN_PROGRESS |
			   fRTMP_ADAPTER_RADIO_OFF |
			   fRTMP_ADAPTER_NIC_NOT_EXIST |
			   fRTMP_ADAPTER_BSS_SCAN_IN_PROGRESS) ||
	    OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE)
#ifdef RT30xx
	    || (pAd->EepromAccess)
#endif /* RT30xx // */
#ifdef RT3090
	    || (pAd->bPCIclkOff == TRUE)
#endif /* RT3090 // */
	    )
		return;
