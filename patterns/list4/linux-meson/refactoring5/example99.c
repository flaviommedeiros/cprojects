#ifdef CONFIG_CONCURRENT_MODE
if (padapter->iface_type == IFACE_PORT1)
			{
				val8 = rtw_read8(padapter, REG_DWBCN1_CTRL_8723B+2);
				*val = (BIT(0) & val8) ? _TRUE:_FALSE;
			}
			else
#endif
			{
				// BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2
				val8 = rtw_read8(padapter, REG_TDECTRL+2);
				*val = (BIT(0) & val8) ? _TRUE:_FALSE;
			}
