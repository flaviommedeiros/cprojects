#ifdef CONFIG_CONCURRENT_MODE
if (padapter->iface_type == IFACE_PORT1)
	{
		// reset TSF1
		rtw_write8(padapter, REG_DUAL_TSF_RST, BIT(1));

		// disable update TSF1
		val8 = rtw_read8(padapter, REG_BCN_CTRL_1);
		val8 |= DIS_TSF_UDT;
		rtw_write8(padapter, REG_BCN_CTRL_1, val8);
		
		// disable Port1's beacon function
		val8 = rtw_read8(padapter, REG_BCN_CTRL_1);
		val8 &= ~EN_BCN_FUNCTION;
		rtw_write8(padapter, REG_BCN_CTRL_1, val8);
	}
	else
#endif
	{
		// reset TSF
		rtw_write8(padapter, REG_DUAL_TSF_RST, BIT(0));

		// disable update TSF
		val8 = rtw_read8(padapter, REG_BCN_CTRL);
		val8 |= DIS_TSF_UDT;
		rtw_write8(padapter, REG_BCN_CTRL, val8);
	}
