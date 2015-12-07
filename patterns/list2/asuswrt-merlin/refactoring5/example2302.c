#ifdef TO_DO_LIST
if(Adapter->bInHctTest)
		pHalData->ReceiveConfig	=	pHalData->CSMethod |
						RCR_AMF | RCR_ADF |	//RCR_AAP | 	//accept management/data
						//guangan200710
						RCR_ACF |	//accept control frame for SW AP needs PS-poll, 2005.07.07, by rcnjko.
						RCR_AB | RCR_AM | RCR_APM |		//accept BC/MC/UC
						RCR_AICV | RCR_ACRC32 | 		//accept ICV/CRC error packet
						((u32)7<<RCR_MXDMA_OFFSET) | // Max DMA Burst Size per Rx DMA Burst, 7: unlimited.
						(pHalData->EarlyRxThreshold<<RCR_FIFO_OFFSET) | // Rx FIFO Threshold, 7: No Rx threshold.
						(pHalData->EarlyRxThreshold == 7 ? RCR_OnlyErlPkt:0);
	else

#endif
	priv->ReceiveConfig	=
		RCR_AMF | RCR_ADF |		//accept management/data
		RCR_ACF |			//accept control frame for SW AP needs PS-poll, 2005.07.07, by rcnjko.
		RCR_AB | RCR_AM | RCR_APM |	//accept BC/MC/UC
		//RCR_AICV | RCR_ACRC32 | 	//accept ICV/CRC error packet
		((u32)7<<RCR_MXDMA_OFFSET)| // Max DMA Burst Size per Rx DMA Burst, 7: unlimited.
		(priv->EarlyRxThreshold<<RX_FIFO_THRESHOLD_SHIFT) | // Rx FIFO Threshold, 7: No Rx threshold.
		(priv->EarlyRxThreshold == 7 ? RCR_ONLYERLPKT:0);
