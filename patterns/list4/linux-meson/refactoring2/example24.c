#ifdef CONFIG_CONCURRENT_MODE
if (!check_buddy_mlmeinfo_state(padapter, WIFI_FW_AP_STATE))		
#endif // CONFIG_CONCURRENT_MODE
			{
				StopTxBeacon(padapter);
#ifdef CONFIG_PCI_HCI
				UpdateInterruptMask8723BE(padapter, 0, 0, RT_BCN_INT_MASKS, 0);
#else // !CONFIG_PCI_HCI
#ifdef CONFIG_INTERRUPT_BASED_TXBCN
#ifdef CONFIG_INTERRUPT_BASED_TXBCN_EARLY_INT
				rtw_write8(padapter, REG_DRVERLYINT, 0x05); // restore early int time to 5ms
				UpdateInterruptMask8812AU(padapter, _TRUE, 0, IMR_BCNDMAINT0_8723B);
#endif // CONFIG_INTERRUPT_BASED_TXBCN_EARLY_INT

#ifdef CONFIG_INTERRUPT_BASED_TXBCN_BCN_OK_ERR
				UpdateInterruptMask8812AU(padapter,_TRUE ,0, (IMR_TXBCN0ERR_8723B|IMR_TXBCN0OK_8723B));
#endif // CONFIG_INTERRUPT_BASED_TXBCN_BCN_OK_ERR

#endif // CONFIG_INTERRUPT_BASED_TXBCN
#endif // !CONFIG_PCI_HCI
			}
