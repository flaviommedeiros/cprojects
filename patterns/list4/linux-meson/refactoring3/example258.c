switch (variable) {
		case HW_VAR_INITIAL_GAIN:
			{				
				u8 rx_gain = *((u8 *)(val));
				//printk("rx_gain:%x\n",rx_gain);
				if(rx_gain == 0xff){//restore rx gain					
					//ODM_Write_DIG(podmpriv,pDigTable->BackupIGValue);
					odm_PauseDIG(odm, ODM_RESUME_DIG,rx_gain);
				}
				else{
					//pDigTable->BackupIGValue = pDigTable->CurIGValue;
					//ODM_Write_DIG(podmpriv,rx_gain);
					odm_PauseDIG(odm, ODM_PAUSE_DIG,rx_gain);
				}
			}
			break;		
		case HW_VAR_PORT_SWITCH:
			hw_var_port_switch(adapter);
			break;
		case HW_VAR_INIT_RTS_RATE:
		{
			u16 brate_cfg = *((u16*)val);
			u8 rate_index = 0;
			HAL_VERSION *hal_ver = &hal_data->VersionID;

			if (IS_8188E(*hal_ver)) {

				while (brate_cfg > 0x1) {
					brate_cfg = (brate_cfg >> 1);
					rate_index++;
				}
				rtw_write8(adapter, REG_INIRTS_RATE_SEL, rate_index);
			} else {
				rtw_warn_on(1);
			}
		}
			break;
		case HW_VAR_SEC_CFG:
		{
			#if defined(CONFIG_CONCURRENT_MODE) && !defined(DYNAMIC_CAMID_ALLOC)
			// enable tx enc and rx dec engine, and no key search for MC/BC
			rtw_write8(adapter, REG_SECCFG, SCR_NoSKMC|SCR_RxDecEnable|SCR_TxEncEnable);
			#elif defined(DYNAMIC_CAMID_ALLOC)
			u16 reg_scr;

			reg_scr = rtw_read16(adapter, REG_SECCFG);
			rtw_write16(adapter, REG_SECCFG, reg_scr|SCR_CHK_KEYID|SCR_RxDecEnable|SCR_TxEncEnable);
			#else
			rtw_write8(adapter, REG_SECCFG, *((u8*)val));
			#endif
		}
			break;
		case HW_VAR_SEC_DK_CFG:
		{
			struct security_priv *sec = &adapter->securitypriv;
			u8 reg_scr = rtw_read8(adapter, REG_SECCFG);

			if (val) /* Enable default key related setting */
			{
				reg_scr |= SCR_TXBCUSEDK;
				if (sec->dot11AuthAlgrthm != dot11AuthAlgrthm_8021X)
					reg_scr |= (SCR_RxUseDK|SCR_TxUseDK);
			}
			else /* Disable default key related setting */
			{
				reg_scr &= ~(SCR_RXBCUSEDK|SCR_TXBCUSEDK|SCR_RxUseDK|SCR_TxUseDK);
			}

			rtw_write8(adapter, REG_SECCFG, reg_scr);
		}
			break;
		case HW_VAR_DM_FLAG:
			odm->SupportAbility = *((u32*)val);
			break;
		case HW_VAR_DM_FUNC_OP:
			if (*((u8*)val) == _TRUE) {
				/* save dm flag */
				odm->BK_SupportAbility = odm->SupportAbility;				
			} else {
				/* restore dm flag */
				odm->SupportAbility = odm->BK_SupportAbility;
			}
			break;
		case HW_VAR_DM_FUNC_SET:
			odm->SupportAbility |= *((u32 *)val);
			break;
		case HW_VAR_DM_FUNC_CLR:
			/*
			* input is already a mask to clear function
			* don't invert it again! George,Lucas@20130513
			*/
			odm->SupportAbility &= *((u32 *)val);
			break;
		case HW_VAR_ASIX_IOT:
			// enable  ASIX IOT function
			if (*((u8*)val) == _TRUE) {
				// 0xa2e[0]=0 (disable rake receiver)
				rtw_write8(adapter, rCCK0_FalseAlarmReport+2, 
						rtw_read8(adapter, rCCK0_FalseAlarmReport+2) & ~(BIT0));
				//  0xa1c=0xa0 (reset channel estimation if signal quality is bad)
				rtw_write8(adapter, rCCK0_DSPParameter2, 0xa0);
			} else {
			// restore reg:0xa2e,   reg:0xa1c
				rtw_write8(adapter, rCCK0_FalseAlarmReport+2, 
						rtw_read8(adapter, rCCK0_FalseAlarmReport+2)|(BIT0));
				rtw_write8(adapter, rCCK0_DSPParameter2, 0x00);
			}
			break;
#ifdef CONFIG_WOWLAN
	case HW_VAR_WOWLAN:
	{
		struct wowlan_ioctl_param *poidparam;
		struct pwrctrl_priv *pwrctl = adapter_to_pwrctl(adapter);
		struct security_priv *psecuritypriv = &adapter->securitypriv;
		struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
		struct hal_ops *pHalFunc = &adapter->HalFunc;
		struct sta_info *psta = NULL;
		int res;
		u16 media_status_rpt;
		u8 val8;

		poidparam = (struct wowlan_ioctl_param *)val;
		switch (poidparam->subcode) {
			case WOWLAN_ENABLE:
				DBG_871X_LEVEL(_drv_always_, "WOWLAN_ENABLE\n");

#ifdef CONFIG_GTK_OL
				if (psecuritypriv->dot11PrivacyAlgrthm == _AES_)
					rtw_hal_fw_sync_cam_id(adapter);
#endif
				if (IS_HARDWARE_TYPE_8723B(adapter))
					rtw_hal_backup_rate(adapter);

				rtw_hal_set_wowlan_fw(adapter, _TRUE);

				media_status_rpt = RT_MEDIA_CONNECT;
				rtw_hal_set_hwreg(adapter,
						HW_VAR_H2C_FW_JOINBSSRPT,
						(u8 *)&media_status_rpt);

				if (!pwrctl->wowlan_pno_enable) {
					psta = rtw_get_stainfo(&adapter->stapriv,
							get_bssid(pmlmepriv));
					media_status_rpt =
						(u16)((psta->mac_id<<8)|RT_MEDIA_CONNECT);
					if (psta != NULL) {
						rtw_hal_set_hwreg(adapter,
								HW_VAR_H2C_MEDIA_STATUS_RPT,
								(u8 *)&media_status_rpt);
					}
				}

				rtw_msleep_os(2);

				if (IS_HARDWARE_TYPE_8188E(adapter))
					rtw_hal_disable_tx_report(adapter);

				//RX DMA stop
				res = rtw_hal_pause_rx_dma(adapter);
				if (res == _FAIL)
					DBG_871X_LEVEL(_drv_always_, "[WARNING] pause RX DMA fail\n");

#if defined(CONFIG_SDIO_HCI) || defined(CONFIG_GSPI_HCI)
				//Enable CPWM2 only.
				res = rtw_hal_enable_cpwm2(adapter);
				if (res == _FAIL)
					DBG_871X_LEVEL(_drv_always_, "[WARNING] enable cpwm2 fail\n");
#endif
#ifdef CONFIG_GPIO_WAKEUP
				rtw_hal_switch_gpio_wl_ctrl(adapter,
						WAKEUP_GPIO_IDX, _TRUE);
#endif
				//Set WOWLAN H2C command.
				DBG_871X_LEVEL(_drv_always_, "Set WOWLan cmd\n");
				rtw_hal_set_fw_wow_related_cmd(adapter, 1);

				res = rtw_hal_check_wow_ctrl(adapter, _TRUE);
				if (res == _FALSE)
					DBG_871X("[Error]%s: set wowlan CMD fail!!\n", __func__);

				pwrctl->wowlan_wake_reason =
					rtw_read8(adapter, REG_WOWLAN_WAKE_REASON);

				DBG_871X_LEVEL(_drv_always_,
						"wowlan_wake_reason: 0x%02x\n",
						pwrctl->wowlan_wake_reason);
#ifdef CONFIG_GTK_OL_DBG
				dump_cam_table(adapter);
#endif
#ifdef CONFIG_USB_HCI
				if (adapter->intf_stop)		//free adapter's resource
					adapter->intf_stop(adapter);

#ifdef CONFIG_CONCURRENT_MODE
					if (rtw_buddy_adapter_up(adapter)) { //free buddy adapter's resource
						adapter->pbuddy_adapter->intf_stop(adapter->pbuddy_adapter);
					}
#endif //CONFIG_CONCURRENT_MODE

				/* Invoid SE0 reset signal during suspending*/
				rtw_write8(adapter, REG_RSV_CTRL, 0x20);
				rtw_write8(adapter, REG_RSV_CTRL, 0x60);
#endif //CONFIG_USB_HCI
				break;
			case WOWLAN_DISABLE:
				DBG_871X_LEVEL(_drv_always_, "WOWLAN_DISABLE\n");

				if (!pwrctl->wowlan_pno_enable) {
					psta = rtw_get_stainfo(&adapter->stapriv,
								get_bssid(pmlmepriv));

					if (psta != NULL) {
						media_status_rpt =
							(u16)((psta->mac_id<<8)|RT_MEDIA_DISCONNECT);
						rtw_hal_set_hwreg(adapter,
								HW_VAR_H2C_MEDIA_STATUS_RPT,
								(u8 *)&media_status_rpt);
					} else {
						DBG_871X("%s: psta is null\n", __func__);
					}
				}

				if (0) {
					DBG_871X("0x630:0x%02x\n",
							rtw_read8(adapter, 0x630));
					DBG_871X("0x631:0x%02x\n",
							rtw_read8(adapter, 0x631));
				}

				pwrctl->wowlan_wake_reason = rtw_read8(adapter,
						REG_WOWLAN_WAKE_REASON);

				DBG_871X_LEVEL(_drv_always_, "wakeup_reason: 0x%02x\n",
						pwrctl->wowlan_wake_reason);

				rtw_hal_set_fw_wow_related_cmd(adapter, 0);

				res = rtw_hal_check_wow_ctrl(adapter, _FALSE);
				if (res == _FALSE) {
					DBG_871X("[Error]%s: disable WOW cmd fail\n!!", __func__);
					rtw_hal_force_enable_rxdma(adapter);
				}

				if (IS_HARDWARE_TYPE_8188E(adapter))
					rtw_hal_enable_tx_report(adapter);

				rtw_hal_update_tx_iv(adapter);

#ifdef CONFIG_GTK_OL
				if (psecuritypriv->dot11PrivacyAlgrthm == _AES_)
					rtw_hal_update_gtk_offload_info(adapter);
#endif //CONFIG_GTK_OL

				rtw_hal_set_wowlan_fw(adapter, _FALSE);

#ifdef CONFIG_GPIO_WAKEUP
				DBG_871X_LEVEL(_drv_always_, "Set Wake GPIO to high for default.\n");
				rtw_hal_set_output_gpio(adapter, WAKEUP_GPIO_IDX, 1);
				rtw_hal_switch_gpio_wl_ctrl(adapter,
						WAKEUP_GPIO_IDX, _FALSE);
#endif
				if((pwrctl->wowlan_wake_reason != FWDecisionDisconnect) &&
					(pwrctl->wowlan_wake_reason != Rx_Pairwisekey) &&
					(pwrctl->wowlan_wake_reason != Rx_DisAssoc) &&
					(pwrctl->wowlan_wake_reason != Rx_DeAuth)) {

					//rtw_hal_download_rsvd_page(adapter, RT_MEDIA_CONNECT);

					media_status_rpt = RT_MEDIA_CONNECT;
					rtw_hal_set_hwreg(adapter,
						HW_VAR_H2C_FW_JOINBSSRPT,
						(u8 *)&media_status_rpt);

					if (psta != NULL) {
						media_status_rpt =
							(u16)((psta->mac_id<<8)|RT_MEDIA_CONNECT);
						rtw_hal_set_hwreg(adapter,
								HW_VAR_H2C_MEDIA_STATUS_RPT,
								(u8 *)&media_status_rpt);
					}
				}
				break;
			default:
				break;
			}
		}
		break;
#endif //CONFIG_WOWLAN
#ifdef CONFIG_AP_WOWLAN
		case HW_VAR_AP_WOWLAN:
		{
			u8 trycnt = 100;
			struct wowlan_ioctl_param *poidparam;
			struct pwrctrl_priv *pwrctl = adapter_to_pwrctl(adapter);
			struct security_priv *psecuritypriv = &adapter->securitypriv;
			struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
			struct hal_ops *pHalFunc = &adapter->HalFunc;
			struct sta_info *psta = NULL;
			int res;
			u16 media_status_rpt;
			u8 val8;

			poidparam = (struct wowlan_ioctl_param *) val;
			switch (poidparam->subcode) {
			case WOWLAN_AP_ENABLE:
				DBG_871X("%s, WOWLAN_AP_ENABLE\n", __func__);
				/* 1. Download WOWLAN FW*/
				DBG_871X_LEVEL(_drv_always_, "Re-download WoWlan FW!\n");
#ifdef DBG_CHECK_FW_PS_STATE
				if (rtw_fw_ps_state(adapter) == _FAIL) {
					pdbgpriv->dbg_enwow_dload_fw_fail_cnt++;
					DBG_871X_LEVEL(_drv_always_, "wowlan enable no leave 32k\n");
				}
#endif /*DBG_CHECK_FW_PS_STATE*/
				do {
					if (rtw_read8(adapter, REG_HMETFR) == 0x00) {
						DBG_871X_LEVEL(_drv_always_, "Ready to change FW.\n");
						break;
					}
					rtw_msleep_os(10);
					DBG_871X_LEVEL(_drv_always_, "trycnt: %d\n", (100-trycnt));
				} while (trycnt--);

				if (pHalFunc->hal_set_wowlan_fw != NULL)
					pHalFunc->hal_set_wowlan_fw(adapter, _TRUE);
				else
					DBG_871X("hal_set_wowlan_fw is null\n");

				/* 2. RX DMA stop*/
				DBG_871X_LEVEL(_drv_always_, "Pause DMA\n");
				trycnt = 100;
				rtw_write32(adapter , REG_RXPKT_NUM ,
					(rtw_read32(adapter , REG_RXPKT_NUM)|RW_RELEASE_EN));
				do {
					if ((rtw_read32(adapter, REG_RXPKT_NUM)&RXDMA_IDLE)) {
						DBG_871X_LEVEL(_drv_always_ , "RX_DMA_IDLE is true\n");
						/*if (Adapter->intf_stop)
							Adapter->intf_stop(Adapter);
						*/
						break;
					}
					/* If RX_DMA is not idle, receive one pkt from DMA*/
					DBG_871X_LEVEL(_drv_always_ , "RX_DMA_IDLE is not true\n");
				} while (trycnt--);

				if (trycnt == 0)
					DBG_871X_LEVEL(_drv_always_ , "Stop RX DMA failed......\n");

				/* 5. Set Enable WOWLAN H2C command. */
				DBG_871X_LEVEL(_drv_always_, "Set Enable AP WOWLan cmd\n");
				if (pHalFunc->hal_set_ap_wowlan_cmd != NULL)
					pHalFunc->hal_set_ap_wowlan_cmd(adapter, 1);
				else
					DBG_871X("hal_set_ap_wowlan_cmd is null\n");
		
				/* 6. add some delay for H2C cmd ready*/
				rtw_msleep_os(10);
				/* 7. enable AP power save*/

				rtw_write8(adapter, REG_MCUTST_WOWLAN, 0);

				if (adapter->intf_stop)
					adapter->intf_stop(adapter);

#ifdef CONFIG_USB_HCI 
				
#ifdef CONFIG_CONCURRENT_MODE
				if (rtw_buddy_adapter_up(adapter)) { /*free buddy adapter's resource*/
					adapter->pbuddy_adapter->intf_stop(adapter->pbuddy_adapter);
				}
#endif /*CONFIG_CONCURRENT_MODE*/

				/* Invoid SE0 reset signal during suspending*/
				rtw_write8(adapter, REG_RSV_CTRL, 0x20);
				rtw_write8(adapter, REG_RSV_CTRL, 0x60);
#endif /*CONFIG_USB_HCI*/
				break;
			case WOWLAN_AP_DISABLE:
				DBG_871X("%s, WOWLAN_AP_DISABLE\n", __func__);
				/* 1. Read wakeup reason*/
				pwrctl->wowlan_wake_reason =
					rtw_read8(adapter, REG_MCUTST_WOWLAN);

				DBG_871X_LEVEL(_drv_always_, "wakeup_reason: 0x%02x\n",
						pwrctl->wowlan_wake_reason);

				/* 2. disable AP power save*/
				if (pHalFunc->hal_set_ap_ps_wowlan_cmd != NULL)
					pHalFunc->hal_set_ap_ps_wowlan_cmd(adapter, 0);
				else
					DBG_871X("hal_set_ap_ps_wowlan_cmd is null\n");
				/* 3.  Set Disable WOWLAN H2C command.*/
				DBG_871X_LEVEL(_drv_always_, "Set Disable WOWLan cmd\n");
				if (pHalFunc->hal_set_ap_wowlan_cmd != NULL)
					pHalFunc->hal_set_ap_wowlan_cmd(adapter, 0);
				else
					DBG_871X("hal_set_ap_wowlan_cmd is null\n");
				/* 6. add some delay for H2C cmd ready*/
				rtw_msleep_os(2);
#ifdef DBG_CHECK_FW_PS_STATE
				if (rtw_fw_ps_state(adapter) == _FAIL) {
					pdbgpriv->dbg_diswow_dload_fw_fail_cnt++;
					DBG_871X_LEVEL(_drv_always_, "wowlan enable no leave 32k\n");
				}
#endif /*DBG_CHECK_FW_PS_STATE*/

				DBG_871X_LEVEL(_drv_always_, "Release RXDMA\n");

				rtw_write32(adapter, REG_RXPKT_NUM,
					(rtw_read32(adapter , REG_RXPKT_NUM) & (~RW_RELEASE_EN)));

				do {
					if (rtw_read8(adapter, REG_HMETFR) == 0x00) {
						DBG_871X_LEVEL(_drv_always_, "Ready to change FW.\n");
						break;
					}
					rtw_msleep_os(10);
					DBG_871X_LEVEL(_drv_always_, "trycnt: %d\n", (100-trycnt));
				} while (trycnt--);

				if (pHalFunc->hal_set_wowlan_fw != NULL)
					pHalFunc->hal_set_wowlan_fw(adapter, _FALSE);
				else
					DBG_871X("hal_set_wowlan_fw is null\n");
#ifdef CONFIG_GPIO_WAKEUP
				DBG_871X_LEVEL(_drv_always_, "Set Wake GPIO to high for default.\n");
				rtw_hal_set_output_gpio(adapter, WAKEUP_GPIO_IDX, 1);
#endif

#ifdef CONFIG_CONCURRENT_MODE
				if (rtw_buddy_adapter_up(adapter) == _TRUE &&
					check_buddy_fwstate(adapter, WIFI_AP_STATE) == _TRUE) {
					media_status_rpt = RT_MEDIA_CONNECT;
					rtw_hal_set_hwreg(adapter->pbuddy_adapter , HW_VAR_H2C_FW_JOINBSSRPT , (u8 *)&media_status_rpt);
					issue_beacon(adapter->pbuddy_adapter, 0);
				} else {
					media_status_rpt = RT_MEDIA_CONNECT;
					rtw_hal_set_hwreg(adapter , HW_VAR_H2C_FW_JOINBSSRPT , (u8 *)&media_status_rpt);
					issue_beacon(adapter, 0);
				}
#else
				media_status_rpt = RT_MEDIA_CONNECT;
				rtw_hal_set_hwreg(adapter , HW_VAR_H2C_FW_JOINBSSRPT , (u8 *)&media_status_rpt);
				issue_beacon(adapter , 0);
#endif

				break;
			default:
				break;
			}
		}
			break;
#endif /*CONFIG_AP_WOWLAN*/
		default:
			if (0)
				DBG_871X_LEVEL(_drv_always_, FUNC_ADPT_FMT" variable(%d) not defined!\n",
					FUNC_ADPT_ARG(adapter), variable);
			break;
	}
