#ifdef RT2860
if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE) ||
			RTMP_SET_PSFLAG(pAd, fRTMP_PS_SET_PCI_CLK_OFF_COMMAND) ||
			RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF))
#endif
#ifdef RT2870
		if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE))
#endif
        {
#ifdef RT2860
		    AsicForceWakeup(pAd, RTMP_HALT);
#endif
#ifdef RT2870
		    AsicForceWakeup(pAd, TRUE);
#endif
        }
