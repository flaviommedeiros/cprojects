if (OPSTATUS_TEST_FLAG(pAd, fOP_STATUS_DOZE) ||
#ifdef RTMP_MAC_PCI
		(pAd->bPCIclkOff == TRUE) ||
#endif // RTMP_MAC_PCI //
		RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_IDLE_RADIO_OFF) ||
		RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BSS_SCAN_IN_PROGRESS))
{

#ifdef CARRIER_SENSE_NEW_ALGO
	//KH Add to Fix PCIe Power-Saving bug<--
	RTMP_INT_UNLOCK(&pAd->irq_lock, flags);
	//KH add to fix PCIe-Power Saving -->
#endif // CARRIER_SENSE_NEW_ALGO //
		return;
}
