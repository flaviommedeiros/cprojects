#ifdef CONFIG_CONCURRENT_MODE
if (padapter->iface_type == IFACE_PORT1)
			{
				// SW_BCN_SEL - Port1
				val8 = rtw_read8(padapter, REG_DWBCN1_CTRL_8723B+2);
				val8 |= BIT(4);
				rtw_write8(padapter, REG_DWBCN1_CTRL_8723B+2, val8);
			}
			else
#endif // CONFIG_CONCURRENT_MODE
			{
				// SW_BCN_SEL - Port0
				val8 = rtw_read8(padapter, REG_DWBCN1_CTRL_8723B+2);
				val8 &= ~BIT(4);
				rtw_write8(padapter, REG_DWBCN1_CTRL_8723B+2, val8);	
			}
