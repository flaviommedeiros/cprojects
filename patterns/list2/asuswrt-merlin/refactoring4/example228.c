#ifdef BCM_WL_EMULATOR
if ((skb = (struct sk_buff *)wlcemu_pktget(pDevice->wlc,pPacket->u.Rx.RxBufferSize + 2)) == 0)
#else 
	       if ((skb = dev_alloc_skb(pPacket->u.Rx.RxBufferSize + 2 + EXTRA_HDR)) == 0)
#endif /* BCM_WL_EMULATOR  */
	       {
		       QQ_PushHead(&pUmDevice->rx_out_of_buf_q.Container,
		                   pPacket);
		       ret = 1;
		       break;
	       }
