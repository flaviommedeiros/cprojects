switch (pC2hEvent->CmdID)
	{
		case C2H_AP_RPT_RSP:
			#if 0
			{
			
				u4Byte c2h_ap_keeplink = _TRUE;
				if (c2hBuf[2] == 0 && c2hBuf[3] == 0)
					c2h_ap_keeplink = _FALSE;
				else
					c2h_ap_keeplink = _TRUE;

				if (_TRUE == pmlmeext->try_ap_c2h_wait) {
					if (_FALSE == c2h_ap_keeplink) {
						pmlmeext->try_ap_c2h_wait = _FALSE;
						RT_TRACE(_module_hal_init_c_, _drv_err_,("fw tell us link is off\n"));
						receive_disconnect(padapter, pmlmeinfo->network.MacAddress , 65535);
					} else	{
						RT_TRACE(_module_hal_init_c_, _drv_err_,("fw tell us link is on\n"));
					}
				} else {
					RT_TRACE(_module_hal_init_c_, _drv_err_,("we don't need this C2H\n"));
				}
				pmlmeext->check_ap_processing = _FALSE;
			}
			#endif
			break;
		case C2H_DBG:
			{
				RT_TRACE(_module_hal_init_c_, _drv_info_, ("C2HCommandHandler: %s\n", c2hBuf));
			}
			break;

		case C2H_CCX_TX_RPT:
			CCX_FwC2HTxRpt_8723b(padapter, c2hBuf, pC2hEvent->CmdLen);
			break;

#ifdef CONFIG_BT_COEXIST
#ifdef CONFIG_PCI_HCI
		case C2H_BT_RSSI:
//			fwc2h_ODM(padapter, tmpBuf, &C2hEvent);
			//BT_FwC2hBtRssi(padapter, c2hBuf);
			break;
#endif
#endif

		case C2H_EXT_RA_RPT:
//			C2HExtRaRptHandler(padapter, tmpBuf, C2hEvent.CmdLen);
			break;

		case C2H_HW_INFO_EXCH:
			RT_TRACE(_module_hal_init_c_, _drv_info_, ("[BT], C2H_HW_INFO_EXCH\n"));
			for (index = 0; index < pC2hEvent->CmdLen; index++)
			{
				RT_TRACE(_module_hal_init_c_, _drv_info_, ("[BT], tmpBuf[%d]=0x%x\n", index, c2hBuf[index]));
			}
			break;

#ifdef CONFIG_BT_COEXIST
		case C2H_8723B_BT_INFO:
			rtw_btcoex_BtInfoNotify(padapter, pC2hEvent->CmdLen, c2hBuf);
			break;
#endif

#ifdef CONFIG_MP_INCLUDED
		case C2H_8723B_BT_MP_INFO:
			MPTBT_FwC2hBtMpCtrl(padapter, c2hBuf, pC2hEvent->CmdLen);
			break;
#endif

#ifdef CONFIG_FW_C2H_DEBUG
		case C2H_8723B_FW_DEBUG:
			Debug_FwC2H(padapter, c2hBuf, pC2hEvent->CmdLen);
			break;
#endif // CONFIG_FW_C2H_DEBUG

		default:
			break;
	}
