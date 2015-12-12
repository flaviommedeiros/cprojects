if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS	|
							fRTMP_ADAPTER_HALT_IN_PROGRESS	|
							fRTMP_ADAPTER_RADIO_OFF			|
							fRTMP_ADAPTER_NIC_NOT_EXIST)
							|| OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE)
#ifdef RT2870
							|| (pAd->EepromAccess)
#endif
							)
		return;
