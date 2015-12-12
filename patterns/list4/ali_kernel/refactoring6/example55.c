if ((pAd->OpMode == OPMODE_AP) ||
        ((pAd->OpMode == OPMODE_STA)
        && (!OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_PCIE_DEVICE)
#ifdef CONFIG_STA_SUPPORT
        ||pAd->StaCfg.PSControl.field.EnableNewPS == FALSE
#endif // CONFIG_STA_SUPPORT //
        )))
    {
	RT28xxPciAsicRadioOn(pAd, GUI_IDLE_POWER_SAVE);
	//NICResetFromError(pAd);

	RTMPRingCleanUp(pAd, QID_AC_BK);
	RTMPRingCleanUp(pAd, QID_AC_BE);
	RTMPRingCleanUp(pAd, QID_AC_VI);
	RTMPRingCleanUp(pAd, QID_AC_VO);
	/*RTMPRingCleanUp(pAd, QID_HCCA);*/
	RTMPRingCleanUp(pAd, QID_MGMT);
	RTMPRingCleanUp(pAd, QID_RX);

	// Enable Tx/Rx
	RTMPEnableRxTx(pAd);

	// Clear Radio off flag
	RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_RADIO_OFF);
	RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF);
	    // Set LED
	    RTMPSetLED(pAd, LED_RADIO_ON);
    }
