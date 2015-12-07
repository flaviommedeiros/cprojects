#if HCF_ENCAP == HCF_ENC
if ( ifbp->IFB_CKIPStat == HCF_ACT_CCX_OFF )
#endif // HCF_TYPE_CCX
    {
int i;
DESC_STRCT *p = descp->next_desc_addr;	//pointer to 2nd descriptor of frame
		HCFASSERT(p, 0)
		// The 2nd descriptor contains (maybe) a SNAP header plus part or whole of the payload.
		//determine decapsulation sub-flag in RxFS
		i = *(wci_recordp)&descp->buf_addr[HFS_STAT] & ( HFS_STAT_MSG_TYPE | HFS_STAT_ERR );
		if ( i == HFS_STAT_TUNNEL ||
			 ( i == HFS_STAT_1042 && hcf_encap( (wci_bufp)&p->buf_addr[HCF_DASA_SIZE] ) != ENC_TUNNEL )) {
			// The 2nd descriptor contains a SNAP header plus part or whole of the payload.
			HCFASSERT( p->BUF_CNT == (p->buf_addr[5] + (p->buf_addr[4]<<8) + 2*6 + 2 - 8), p->BUF_CNT )
			// perform decapsulation
			HCFASSERT(p->BUF_SIZE >=8, p->BUF_SIZE)
			// move SA[2:5] in the second buffer to replace part of the SNAP header
			for ( i=3; i >= 0; i--) p->buf_addr[i+8] = p->buf_addr[i];
			// copy DA[0:5], SA[0:1] from first buffer to second buffer
			for ( i=0; i<8; i++) p->buf_addr[i] = descp->buf_addr[HFS_ADDR_DEST + i];
			// make first buffer shorter in count
			descp->BUF_CNT = HFS_ADDR_DEST;
		}
	}
