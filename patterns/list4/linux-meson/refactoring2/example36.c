#ifdef DBG_CONFIG_ERROR_DETECT
if(psrtpriv->silent_reset_inprogress == _FALSE)
#endif //DBG_CONFIG_ERROR_DETECT
	{
	ConstructARPResponse(
		padapter, 
		&ReservedPagePacket[BufIndex],
		&ARPLegnth,
		currentip
		);
	rtl8723b_fill_fake_txdesc(padapter, &ReservedPagePacket[BufIndex-TxDescLen], ARPLegnth, _FALSE, _FALSE, _TRUE);

	//DBG_871X("%s(): HW_VAR_SET_TX_CMD: ARP RSP %p %d\n", 
	//	__FUNCTION__, &ReservedPagePacket[BufIndex-TxDescLen], (ARPLegnth+TxDescLen));

	CurtPktPageNum = (u8)PageNum_128(TxDescLen + ARPLegnth);
	}
#ifdef DBG_CONFIG_ERROR_DETECT
	else
		CurtPktPageNum = (u8)PageNum_128(128);
