#ifdef CONFIG_CONCURRENT_MODE
if (padapter->iface_type == IFACE_PORT1)
			{
				val8 = rtw_read8(padapter,  REG_DWBCN1_CTRL_8723B+2);
				val8 |= BIT(0);
				rtw_write8(padapter, REG_DWBCN1_CTRL_8723B+2, val8); 
			}
			else
#endif // CONFIG_CONCURRENT_MODE
			{
				// BCN_VALID, BIT16 of REG_TDECTRL = BIT0 of REG_TDECTRL+2, write 1 to clear, Clear by sw
				val8 = rtw_read8(padapter, REG_TDECTRL+2);
				val8 |= BIT(0);
				rtw_write8(padapter, REG_TDECTRL+2, val8);
			}
