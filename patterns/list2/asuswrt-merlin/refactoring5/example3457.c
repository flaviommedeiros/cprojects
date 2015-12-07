#ifdef USB_RX_AGGREGATION_SUPPORT
if (pstats->bisrxaggrsubframe)
		return (sizeof(rx_desc_819x_usb) + pstats->RxDrvInfoSize
			+ pstats->RxBufShift + 8);
	else
#endif
		return (sizeof(rx_desc_819x_usb) + pstats->RxDrvInfoSize
				+ pstats->RxBufShift);
