#ifdef USB_RX_AGGREGATION_SUPPORT
if (bIsRxAggrSubframe)
	{
		rx_desc_819x_usb_aggr_subframe *desc = (rx_desc_819x_usb_aggr_subframe *)skb->data;
		stats->Length = desc->Length ;
		stats->RxDrvInfoSize = desc->RxDrvInfoSize;
		stats->RxBufShift = 0; //RxBufShift = 2 in RxDesc, but usb didn't shift bytes in fact.
		stats->bICV = desc->ICV;
		stats->bCRC = desc->CRC32;
		stats->bHwError = stats->bCRC|stats->bICV;
		stats->Decrypted = !desc->SWDec;//RTL8190 set this bit to indicate that Hw does not decrypt packet
	} else
#endif
	{
		rx_desc_819x_usb *desc = (rx_desc_819x_usb *)skb->data;

		stats->Length = desc->Length;
		stats->RxDrvInfoSize = desc->RxDrvInfoSize;
		stats->RxBufShift = 0;//desc->Shift&0x03;
		stats->bICV = desc->ICV;
		stats->bCRC = desc->CRC32;
		stats->bHwError = stats->bCRC|stats->bICV;
		//RTL8190 set this bit to indicate that Hw does not decrypt packet
		stats->Decrypted = !desc->SWDec;
	}
