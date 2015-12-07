#ifdef USB_TX_DRIVER_AGGREGATION_ENABLE
if (tcb_desc->drv_agg_enable) {
		tx_desc->TxBufferSize = tcb_desc->pkt_size + sizeof(tx_fwinfo_819x_usb);
	} else
#endif
	{
		//DWORD 2
		tx_desc->TxBufferSize = (u32)(skb->len - USB_HWDESC_HEADER_LEN);
	}
