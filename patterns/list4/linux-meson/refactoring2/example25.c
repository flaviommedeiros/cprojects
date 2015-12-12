#ifdef CONFIG_CONCURRENT_MODE
if (check_buddy_mlmeinfo_state(padapter, _HW_STATE_NOLINK_))
#endif
	{
		// Set RCR to not to receive data frame when NO LINK state
		//rtw_write32(padapter, REG_RCR, rtw_read32(padapter, REG_RCR) & ~RCR_ADF);
		// reject all data frames
		rtw_write16(padapter, REG_RXFLTMAP2, 0);
	}
