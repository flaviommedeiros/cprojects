switch(id)
	{
		case GEN_MP_IOCTL_SUBCODE(MP_START):
			DBG_871X("871x_driver is only for normal mode, can't enter mp mode\n");
			break;
		case GEN_MP_IOCTL_SUBCODE(READ_REG):
			RegRWStruct = (pRW_Reg)pdata;
			switch (RegRWStruct->width)
			{
				case 1:
					RegRWStruct->value = rtw_read8(padapter, RegRWStruct->offset);
					break;
				case 2:
					RegRWStruct->value = rtw_read16(padapter, RegRWStruct->offset);
					break;
				case 4:
					RegRWStruct->value = rtw_read32(padapter, RegRWStruct->offset);
					break;
				default:
					break;
			}
		
			break;
		case GEN_MP_IOCTL_SUBCODE(WRITE_REG):
			RegRWStruct = (pRW_Reg)pdata;
			switch (RegRWStruct->width)
			{
				case 1:
					rtw_write8(padapter, RegRWStruct->offset, (u8)RegRWStruct->value);
					break;
				case 2:
					rtw_write16(padapter, RegRWStruct->offset, (u16)RegRWStruct->value);
					break;
				case 4:
					rtw_write32(padapter, RegRWStruct->offset, (u32)RegRWStruct->value);
					break;
				default:					
				break;
			}
				
			break;
		case GEN_MP_IOCTL_SUBCODE(READ_RF_REG):

			prfreg = (struct rf_reg_param *)pdata;

			path = (u8)prfreg->path;		
			offset = (u8)prfreg->offset;	

			value = rtw_hal_read_rfreg(padapter, path, offset, 0xffffffff);

			prfreg->value = value;

			break;			
		case GEN_MP_IOCTL_SUBCODE(WRITE_RF_REG):

			prfreg = (struct rf_reg_param *)pdata;

			path = (u8)prfreg->path;
			offset = (u8)prfreg->offset;	
			value = prfreg->value;

			rtw_hal_write_rfreg(padapter, path, offset, 0xffffffff, value);
			
			break;			
                case GEN_MP_IOCTL_SUBCODE(TRIGGER_GPIO):
			DBG_871X("==> trigger gpio 0\n");
			rtw_hal_set_hwreg(padapter, HW_VAR_TRIGGER_GPIO_0, 0);
			break;	
#ifdef CONFIG_BT_COEXIST
		case GEN_MP_IOCTL_SUBCODE(SET_DM_BT):			
			DBG_871X("==> set dm_bt_coexist:%x\n",*(u8 *)pdata);
			rtw_hal_set_hwreg(padapter, HW_VAR_BT_SET_COEXIST, pdata);
			break;
		case GEN_MP_IOCTL_SUBCODE(DEL_BA):
			DBG_871X("==> delete ba:%x\n",*(u8 *)pdata);
			rtw_hal_set_hwreg(padapter, HW_VAR_BT_ISSUE_DELBA, pdata);
			break;
#endif
#ifdef DBG_CONFIG_ERROR_DETECT
		case GEN_MP_IOCTL_SUBCODE(GET_WIFI_STATUS):							
			*pdata = rtw_hal_sreset_get_wifi_status(padapter);                   
			break;
#endif
	
		default:
			break;
	}
