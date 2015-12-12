switch (variable)
	{
		case HW_VAR_TXPAUSE:
			*val = rtw_read8(padapter, REG_TXPAUSE);
			break;

		case HW_VAR_BCN_VALID:
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
			break;

		case HW_VAR_FWLPS_RF_ON:
			{
				// When we halt NIC, we should check if FW LPS is leave.
				u32 valRCR;

				if ((padapter->bSurpriseRemoved == _TRUE) ||
					(adapter_to_pwrctl(padapter)->rf_pwrstate == rf_off))
				{
					// If it is in HW/SW Radio OFF or IPS state, we do not check Fw LPS Leave,
					// because Fw is unload.
					*val = _TRUE;
				}
				else
				{
					valRCR = rtw_read32(padapter, REG_RCR);
					valRCR &= 0x00070000;
					if(valRCR)
						*val = _FALSE;
					else
						*val = _TRUE;
				}
			}
			break;

#ifdef CONFIG_ANTENNA_DIVERSITY
		case HW_VAR_CURRENT_ANTENNA:
			*val = pHalData->CurAntenna;
			break;
#endif

		case HW_VAR_EFUSE_USAGE:
			*val = pHalData->EfuseUsedPercentage;
			break;

		case HW_VAR_EFUSE_BYTES:
			*((u16*)val) = pHalData->EfuseUsedBytes;
			break;

		case HW_VAR_EFUSE_BT_USAGE:
#ifdef HAL_EFUSE_MEMORY
			*val = pHalData->EfuseHal.BTEfuseUsedPercentage;
#endif
			break;

		case HW_VAR_EFUSE_BT_BYTES:
#ifdef HAL_EFUSE_MEMORY
			*((u16*)val) = pHalData->EfuseHal.BTEfuseUsedBytes;
#else
			*((u16*)val) = BTEfuseUsedBytes;
#endif
			break;

		case HW_VAR_APFM_ON_MAC:
			*val = pHalData->bMacPwrCtrlOn;
			break;
		case HW_VAR_CHK_HI_QUEUE_EMPTY:
			val16 = rtw_read16(padapter, REG_TXPKT_EMPTY);
			*val = (val16 & BIT(10)) ? _TRUE:_FALSE;
			break;
#ifdef CONFIG_WOWLAN
		case HW_VAR_RPWM_TOG:
			*val = rtw_read8(padapter, SDIO_LOCAL_BASE|SDIO_REG_HRPWM1) & BIT7;
			break;
		case HW_VAR_WAKEUP_REASON:
			*val = rtw_read8(padapter, REG_WOWLAN_WAKE_REASON);
			if(*val == 0xEA)
				*val = 0;
			break;
		case HW_VAR_SYS_CLKR:
			*val = rtw_read8(padapter, REG_SYS_CLKR);
			break;
#endif
		case HW_VAR_DUMP_MAC_QUEUE_INFO:
			dump_mac_qinfo_8723b(val, padapter);
			break;
		default:
			GetHwReg(padapter, variable, val);
			break;
	}
