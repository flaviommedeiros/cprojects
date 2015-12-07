#ifdef USB_RX_AGGREGATION_SUPPORT
if (bIsRxAggrSubframe)
		return (sizeof(rx_desc_819x_usb) + Status->RxDrvInfoSize
			+ Status->RxBufShift + 8);
	else
#endif
		return (sizeof(rx_desc_819x_usb) + Status->RxDrvInfoSize
				+ Status->RxBufShift);
