#ifdef USB_TX_DRIVER_AGGREGATION_ENABLE
if (tcb_desc->drv_agg_enable) {
		tx_desc->PktSize = tcb_desc->pkt_size;
	} else
#endif
	{
		tx_desc->PktSize = (skb->len - TX_PACKET_SHIFT_BYTES) & 0xffff;
	}
