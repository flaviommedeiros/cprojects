#ifdef FORE200E_52BYTE_AAL0_SDU
if ((vcc->qos.aal == ATM_AAL0) && (vcc->qos.txtp.max_sdu == ATM_AAL0_SDU)) {
	cell_header = (u32*) skb->data;
	skb_data    = skb->data + 4;    /* skip 4-byte cell header */
	skb_len     = tx_len = skb->len  - 4;

	DPRINTK(3, "user-supplied cell header = 0x%08x\n", *cell_header);
    }
    else 
#endif
    {
	skb_data = skb->data;
	skb_len  = skb->len;
    }
