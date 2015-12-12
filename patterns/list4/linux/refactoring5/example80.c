#ifdef TO_DO_LIST
if (Adapter->bInHctTest)
		pHalData->ReceiveConfig =
			pHalData->CSMethod |
			/* accept management/data */
			RCR_AMF | RCR_ADF |
			/* accept control frame for SW
			 * AP needs PS-poll
			 */
			RCR_ACF |
			/* accept BC/MC/UC */
			RCR_AB | RCR_AM | RCR_APM |
			/* accept ICV/CRC error
			 * packet
			 */
			RCR_AICV | RCR_ACRC32 |
			/* Max DMA Burst Size per Tx
			 * DMA Burst, 7: unlimited.
			 */
			((u32)7 << RCR_MXDMA_OFFSET) |
			/* Rx FIFO Threshold,
			 * 7: No Rx threshold.
			 */
			(pHalData->EarlyRxThreshold << RCR_FIFO_OFFSET) |
			(pHalData->EarlyRxThreshold == 7 ? RCR_OnlyErlPkt : 0);
	else

#endif
	priv->ReceiveConfig	=
		/* accept management/data */
		RCR_AMF | RCR_ADF |
		/* accept control frame for SW AP needs PS-poll */
		RCR_ACF |
		/* accept BC/MC/UC */
		RCR_AB | RCR_AM | RCR_APM |
		/* Max DMA Burst Size per Rx DMA Burst, 7: unlimited. */
		((u32)7 << RCR_MXDMA_OFFSET) |
		/* Rx FIFO Threshold, 7: No Rx threshold. */
		(priv->EarlyRxThreshold << RX_FIFO_THRESHOLD_SHIFT) |
		(priv->EarlyRxThreshold == 7 ? RCR_ONLYERLPKT : 0);
