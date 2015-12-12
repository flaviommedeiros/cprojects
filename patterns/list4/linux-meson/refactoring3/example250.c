switch (variable)
	{
		case HW_VAR_MEDIA_STATUS:
			val8 = rtw_read8(padapter, MSR) & 0x0c;
			val8 |= *val;
			rtw_write8(padapter, MSR, val8);
			break;

		case HW_VAR_MEDIA_STATUS1:
			val8 = rtw_read8(padapter, MSR) & 0x03;
			val8 |= *val << 2;
			rtw_write8(padapter, MSR, val8);
			break;

		case HW_VAR_SET_OPMODE:
			hw_var_set_opmode(padapter, variable, val);
			break;

		case HW_VAR_MAC_ADDR:
			hw_var_set_macaddr(padapter, variable, val);
			break;

		case HW_VAR_BSSID:
			hw_var_set_bssid(padapter, variable, val);
			break;

		case HW_VAR_BASIC_RATE:
		{
			struct mlme_ext_info *mlmext_info = &padapter->mlmeextpriv.mlmext_info;
			u16 input_b = 0, masked = 0, ioted = 0, BrateCfg = 0;
			u16 rrsr_2g_force_mask = (RRSR_11M|RRSR_5_5M|RRSR_1M);
			u16 rrsr_2g_allow_mask = (RRSR_24M|RRSR_12M|RRSR_6M|RRSR_CCK_RATES);

			HalSetBrateCfg(padapter, val, &BrateCfg);
			input_b = BrateCfg;

			/* apply force and allow mask */
			BrateCfg |= rrsr_2g_force_mask;
			BrateCfg &= rrsr_2g_allow_mask;
			masked = BrateCfg;

			#ifdef CONFIG_CMCC_TEST
			BrateCfg |= (RRSR_11M|RRSR_5_5M|RRSR_1M); /* use 11M to send ACK */
			BrateCfg |= (RRSR_24M|RRSR_18M|RRSR_12M); //CMCC_OFDM_ACK 12/18/24M
			#endif

			/* IOT consideration */
			if (mlmext_info->assoc_AP_vendor == HT_IOT_PEER_CISCO) {
				/* if peer is cisco and didn't use ofdm rate, we enable 6M ack */
				if((BrateCfg & (RRSR_24M|RRSR_12M|RRSR_6M)) == 0)
					BrateCfg |= RRSR_6M;
			}
			ioted = BrateCfg;

			pHalData->BasicRateSet = BrateCfg;

			DBG_8192C("HW_VAR_BASIC_RATE: %#x -> %#x -> %#x\n", input_b, masked, ioted);

			// Set RRSR rate table.
			rtw_write16(padapter, REG_RRSR, BrateCfg);
			rtw_write8(padapter, REG_RRSR+2, rtw_read8(padapter, REG_RRSR+2)&0xf0);
		}
			break;

		case HW_VAR_TXPAUSE:
			rtw_write8(padapter, REG_TXPAUSE, *val);
			break;

		case HW_VAR_BCN_FUNC:
			hw_var_set_bcn_func(padapter, variable, val);
			break;

		case HW_VAR_CORRECT_TSF:
			hw_var_set_correct_tsf(padapter, variable, val);
			break;

		case HW_VAR_CHECK_BSSID:
			{
				u32 val32;
				val32 = rtw_read32(padapter, REG_RCR);
				if (*val)
					val32 |= RCR_CBSSID_DATA|RCR_CBSSID_BCN;
				else
					val32 &= ~(RCR_CBSSID_DATA|RCR_CBSSID_BCN);
				rtw_write32(padapter, REG_RCR, val32);
			}
			break;

		case HW_VAR_MLME_DISCONNECT:
			hw_var_set_mlme_disconnect(padapter, variable, val);
			break;

		case HW_VAR_MLME_SITESURVEY:
			hw_var_set_mlme_sitesurvey(padapter, variable,  val);

#ifdef CONFIG_BT_COEXIST
			rtw_btcoex_ScanNotify(padapter, *val?_TRUE:_FALSE);
#endif // CONFIG_BT_COEXIST
			break;

		case HW_VAR_MLME_JOIN:
			hw_var_set_mlme_join(padapter, variable, val);

#ifdef CONFIG_BT_COEXIST
			switch (*val)
			{
				case 0:
					// prepare to join
					rtw_btcoex_ConnectNotify(padapter, _TRUE);
					break;
				case 1:
					// joinbss_event callback when join res < 0
					rtw_btcoex_ConnectNotify(padapter, _FALSE);
					break;
				case 2:
					// sta add event callback
//					rtw_btcoex_MediaStatusNotify(padapter, RT_MEDIA_CONNECT);
					break;
			}
#endif // CONFIG_BT_COEXIST
			break;

		case HW_VAR_ON_RCR_AM:
			val32 = rtw_read32(padapter, REG_RCR);
			val32 |= RCR_AM;
			rtw_write32(padapter, REG_RCR, val32);
			DBG_8192C("%s, %d, RCR= %x\n", __FUNCTION__, __LINE__, rtw_read32(padapter, REG_RCR));
			break;

		case HW_VAR_OFF_RCR_AM:
			val32 = rtw_read32(padapter, REG_RCR);
			val32 &= ~RCR_AM;
			rtw_write32(padapter, REG_RCR, val32);
			DBG_8192C("%s, %d, RCR= %x\n", __FUNCTION__, __LINE__, rtw_read32(padapter, REG_RCR));
			break;

		case HW_VAR_BEACON_INTERVAL:
			rtw_write16(padapter, REG_BCN_INTERVAL, *((u16*)val));
			break;

		case HW_VAR_SLOT_TIME:
			rtw_write8(padapter, REG_SLOT, *val);
			break;

		case HW_VAR_RESP_SIFS:
#if 0
			// SIFS for OFDM Data ACK
			rtw_write8(padapter, REG_SIFS_CTX+1, val[0]);
			// SIFS for OFDM consecutive tx like CTS data!
			rtw_write8(padapter, REG_SIFS_TRX+1, val[1]);

			rtw_write8(padapter, REG_SPEC_SIFS+1, val[0]);
			rtw_write8(padapter, REG_MAC_SPEC_SIFS+1, val[0]);

			// 20100719 Joseph: Revise SIFS setting due to Hardware register definition change.
			rtw_write8(padapter, REG_R2T_SIFS+1, val[0]);
			rtw_write8(padapter, REG_T2T_SIFS+1, val[0]);

#else
			//SIFS_Timer = 0x0a0a0808;
			//RESP_SIFS for CCK
			rtw_write8(padapter, REG_RESP_SIFS_CCK, val[0]); // SIFS_T2T_CCK (0x08)
			rtw_write8(padapter, REG_RESP_SIFS_CCK+1, val[1]); //SIFS_R2T_CCK(0x08)
			//RESP_SIFS for OFDM
			rtw_write8(padapter, REG_RESP_SIFS_OFDM, val[2]); //SIFS_T2T_OFDM (0x0a)
			rtw_write8(padapter, REG_RESP_SIFS_OFDM+1, val[3]); //SIFS_R2T_OFDM(0x0a)
#endif
			break;

		case HW_VAR_ACK_PREAMBLE:
			{
				u8 regTmp;
				u8 bShortPreamble = *val;

				// Joseph marked out for Netgear 3500 TKIP channel 7 issue.(Temporarily)
				//regTmp = (pHalData->nCur40MhzPrimeSC)<<5;
				regTmp = 0;
				if (bShortPreamble) regTmp |= 0x80;
				rtw_write8(padapter, REG_RRSR+2, regTmp);
			}
			break;

		case HW_VAR_CAM_EMPTY_ENTRY:
			{
				u8	ucIndex = *val;
				u8	i;
				u32	ulCommand = 0;
				u32	ulContent = 0;
				u32	ulEncAlgo = CAM_AES;

				for (i=0; i<CAM_CONTENT_COUNT; i++)
				{
					// filled id in CAM config 2 byte
					if (i == 0)
					{
						ulContent |= (ucIndex & 0x03) | ((u16)(ulEncAlgo)<<2);
						//ulContent |= CAM_VALID;
					}
					else
					{
						ulContent = 0;
					}
					// polling bit, and No Write enable, and address
					ulCommand = CAM_CONTENT_COUNT*ucIndex+i;
					ulCommand = ulCommand | CAM_POLLINIG | CAM_WRITE;
					// write content 0 is equall to mark invalid
					rtw_write32(padapter, WCAMI, ulContent);  //delay_ms(40);
					//RT_TRACE(COMP_SEC, DBG_LOUD, ("CAM_empty_entry(): WRITE A4: %lx \n",ulContent));
					rtw_write32(padapter, RWCAM, ulCommand);  //delay_ms(40);
					//RT_TRACE(COMP_SEC, DBG_LOUD, ("CAM_empty_entry(): WRITE A0: %lx \n",ulCommand));
				}
			}
			break;

		case HW_VAR_CAM_INVALID_ALL:
			rtw_write32(padapter, RWCAM, BIT(31)|BIT(30));
			break;

		case HW_VAR_CAM_WRITE:
			{
				u32 cmd;
				u32 *cam_val = (u32*)val;

				rtw_write32(padapter, WCAMI, cam_val[0]);

				cmd = CAM_POLLINIG | CAM_WRITE | cam_val[1];
				rtw_write32(padapter, RWCAM, cmd);
			}
			break;

		case HW_VAR_AC_PARAM_VO:
			rtw_write32(padapter, REG_EDCA_VO_PARAM, *((u32*)val));
			break;

		case HW_VAR_AC_PARAM_VI:
			rtw_write32(padapter, REG_EDCA_VI_PARAM, *((u32*)val));
			break;

		case HW_VAR_AC_PARAM_BE:
			pHalData->AcParam_BE = ((u32*)(val))[0];
			rtw_write32(padapter, REG_EDCA_BE_PARAM, *((u32*)val));
			break;

		case HW_VAR_AC_PARAM_BK:
			rtw_write32(padapter, REG_EDCA_BK_PARAM, *((u32*)val));
			break;

		case HW_VAR_ACM_CTRL:
			{
				u8 ctrl = *((u8*)val);
				u8 hwctrl = 0;

				if (ctrl != 0)
				{
					hwctrl |= AcmHw_HwEn;

					if (ctrl & BIT(1)) // BE
						hwctrl |= AcmHw_BeqEn;

					if (ctrl & BIT(2)) // VI
						hwctrl |= AcmHw_ViqEn;

					if (ctrl & BIT(3)) // VO
						hwctrl |= AcmHw_VoqEn;
				}

				DBG_8192C("[HW_VAR_ACM_CTRL] Write 0x%02X\n", hwctrl);
				rtw_write8(padapter, REG_ACMHWCTRL, hwctrl);
			}
			break;

		case HW_VAR_AMPDU_FACTOR:
			{
				u32	AMPDULen =  (*((u8 *)val));

				if(AMPDULen < HT_AGG_SIZE_32K)
					AMPDULen = (0x2000 << (*((u8 *)val))) -1;
				else
					AMPDULen = 0x7fff;

				rtw_write32(padapter, REG_AMPDU_MAX_LENGTH_8723B, AMPDULen);
			}
			break;

#if 0
		case HW_VAR_RXDMA_AGG_PG_TH:
			rtw_write8(padapter, REG_RXDMA_AGG_PG_TH, *val);
			break;
#endif

		case HW_VAR_H2C_FW_PWRMODE:
			{
				u8 psmode = *val;

				// Forece leave RF low power mode for 1T1R to prevent conficting setting in Fw power
				// saving sequence. 2010.06.07. Added by tynli. Suggested by SD3 yschang.
				if (psmode != PS_MODE_ACTIVE)
				{
					ODM_RF_Saving(&pHalData->odmpriv, _TRUE);
				}

				//if (psmode != PS_MODE_ACTIVE)	{
				//	rtl8723b_set_lowpwr_lps_cmd(padapter, _TRUE);
				//} else {
				//	rtl8723b_set_lowpwr_lps_cmd(padapter, _FALSE);
				//}
				rtl8723b_set_FwPwrMode_cmd(padapter, psmode);
			}
			break;
		case HW_VAR_H2C_PS_TUNE_PARAM:
			rtl8723b_set_FwPsTuneParam_cmd(padapter);
			break;
			
		case HW_VAR_H2C_FW_JOINBSSRPT:
			rtl8723b_set_FwJoinBssRpt_cmd(padapter, *val);
			break;

#ifdef CONFIG_P2P
		case HW_VAR_H2C_FW_P2P_PS_OFFLOAD:
			rtl8723b_set_p2p_ps_offload_cmd(padapter, *val);
			break;
#endif //CONFIG_P2P
#ifdef CONFIG_TDLS
		case HW_VAR_TDLS_WRCR:
			rtw_write32(padapter, REG_RCR, rtw_read32(padapter, REG_RCR)&(~RCR_CBSSID_DATA ));
			break;
		case HW_VAR_TDLS_RS_RCR:
			rtw_write32(padapter, REG_RCR, rtw_read32(padapter, REG_RCR)|(RCR_CBSSID_DATA));
			break;
#endif //CONFIG_TDLS
#ifdef CONFIG_SW_ANTENNA_DIVERSITY
		case HW_VAR_ANTENNA_DIVERSITY_LINK:
			//SwAntDivRestAfterLink8192C(padapter);
			ODM_SwAntDivRestAfterLink(&pHalData->odmpriv);
			break;

		case HW_VAR_ANTENNA_DIVERSITY_SELECT:
			{
				u8 Optimum_antenna = *val;

				//DBG_8192C("==> HW_VAR_ANTENNA_DIVERSITY_SELECT , Ant_(%s)\n",(Optimum_antenna==2)?"A":"B");

				//PHY_SetBBReg(padapter, rFPGA0_XA_RFInterfaceOE, 0x300, Optimum_antenna);
				ODM_SetAntenna(&pHalData->odmpriv, Optimum_antenna);
			}
			break;
#endif

		case HW_VAR_EFUSE_USAGE:
			pHalData->EfuseUsedPercentage = *val;
			break;

		case HW_VAR_EFUSE_BYTES:
			pHalData->EfuseUsedBytes = *((u16*)val);
			break;

		case HW_VAR_EFUSE_BT_USAGE:
#ifdef HAL_EFUSE_MEMORY
			pHalData->EfuseHal.BTEfuseUsedPercentage = *val;
#endif
			break;

		case HW_VAR_EFUSE_BT_BYTES:
#ifdef HAL_EFUSE_MEMORY
			pHalData->EfuseHal.BTEfuseUsedBytes = *((u16*)val);
#else
			BTEfuseUsedBytes = *((u16*)val);
#endif
			break;

		case HW_VAR_FIFO_CLEARN_UP:
			{
				#define RW_RELEASE_EN		BIT(18)
				#define RXDMA_IDLE			BIT(17)

				struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
				u8 trycnt = 100;

				// pause tx
				rtw_write8(padapter, REG_TXPAUSE, 0xff);

				// keep sn
				padapter->xmitpriv.nqos_ssn = rtw_read16(padapter, REG_NQOS_SEQ);

				if (pwrpriv->bkeepfwalive != _TRUE)
				{
					/* RX DMA stop */
					val32 = rtw_read32(padapter, REG_RXPKT_NUM);
					val32 |= RW_RELEASE_EN;
					rtw_write32(padapter, REG_RXPKT_NUM, val32);
					do {
						val32 = rtw_read32(padapter, REG_RXPKT_NUM);
						val32 &= RXDMA_IDLE;
						if (val32)
							break;

						DBG_871X("%s: [HW_VAR_FIFO_CLEARN_UP] val=%x times:%d\n", __FUNCTION__, val32, trycnt);
					} while (--trycnt);
					if (trycnt == 0) {
						DBG_8192C("[HW_VAR_FIFO_CLEARN_UP] Stop RX DMA failed......\n");
					}

					// RQPN Load 0
					rtw_write16(padapter, REG_RQPN_NPQ, 0);
					rtw_write32(padapter, REG_RQPN, 0x80000000);
					rtw_mdelay_os(2);
				}
			}
			break;

#ifdef CONFIG_CONCURRENT_MODE
		case HW_VAR_CHECK_TXBUF:
			{
				u32 i;
				u8 RetryLimit = 0x01;
				u32 reg_200, reg_204;

				val16 = RetryLimit << RETRY_LIMIT_SHORT_SHIFT | RetryLimit << RETRY_LIMIT_LONG_SHIFT;
				rtw_write16(padapter, REG_RL, val16);

				for (i=0; i<200; i++) // polling 200x10=2000 msec  
				{
					reg_200 = rtw_read32(padapter, 0x200);
					reg_204 = rtw_read32(padapter, 0x204);
					if (reg_200 != reg_204)
					{
						//DBG_871X("packet in tx packet buffer - 0x204=%x, 0x200=%x (%d)\n", rtw_read32(padapter, 0x204), rtw_read32(padapter, 0x200), i);
						rtw_msleep_os(10);
					}
					else
					{
						DBG_871X("[HW_VAR_CHECK_TXBUF] no packet in tx packet buffer (%d)\n", i);
						break;
					}
				}

				if (reg_200 != reg_204)
					DBG_871X("packets in tx buffer - 0x204=%x, 0x200=%x\n", reg_204, reg_200);
				
				RetryLimit = 0x30;
				val16 = RetryLimit << RETRY_LIMIT_SHORT_SHIFT | RetryLimit << RETRY_LIMIT_LONG_SHIFT;
				rtw_write16(padapter, REG_RL, val16);
			}
			break;
#endif // CONFIG_CONCURRENT_MODE

		case HW_VAR_APFM_ON_MAC:
			pHalData->bMacPwrCtrlOn = *val;
#ifdef PLATFORM_LINUX
			DBG_8192C("%s: bMacPwrCtrlOn=%d\n", __func__, pHalData->bMacPwrCtrlOn);
#endif
			break;

		case HW_VAR_NAV_UPPER:
			{
				u32 usNavUpper = *((u32*)val);

				if (usNavUpper > HAL_NAV_UPPER_UNIT_8723B * 0xFF)
				{
					RT_TRACE(_module_hal_init_c_, _drv_notice_, ("The setting value (0x%08X us) of NAV_UPPER is larger than (%d * 0xFF)!!!\n", usNavUpper, HAL_NAV_UPPER_UNIT_8723B));
					break;
				}

				// The value of ((usNavUpper + HAL_NAV_UPPER_UNIT_8723B - 1) / HAL_NAV_UPPER_UNIT_8723B)
				// is getting the upper integer.
				usNavUpper = (usNavUpper + HAL_NAV_UPPER_UNIT_8723B - 1) / HAL_NAV_UPPER_UNIT_8723B;
				rtw_write8(padapter, REG_NAV_UPPER, (u8)usNavUpper);
			}
			break;

#ifndef CONFIG_C2H_PACKET_EN
		case HW_VAR_C2H_HANDLE:
			C2HCommandHandler(padapter);
			break;
#endif

		case HW_VAR_H2C_MEDIA_STATUS_RPT:
			{
				u16	mstatus_rpt = (*(u16 *)val);
				u8	mstatus, macId;

				mstatus = (u8) (mstatus_rpt & 0xFF);
				macId = (u8)(mstatus_rpt >> 8)  ;
				rtl8723b_set_FwMediaStatusRpt_cmd(padapter , mstatus, macId);
			}
			break;
		case HW_VAR_BCN_VALID:
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
			break;

		case HW_VAR_DL_BCN_SEL:
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
			break;

		case HW_VAR_DO_IQK:
			pHalData->bNeedIQK = _TRUE;
			break;

		case HW_VAR_DL_RSVD_PAGE:
#ifdef CONFIG_BT_COEXIST
			if (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == _TRUE)
			{
				rtl8723b_download_BTCoex_AP_mode_rsvd_page(padapter);
			}
			else
#endif // CONFIG_BT_COEXIST
			{
				rtl8723b_download_rsvd_page(padapter, RT_MEDIA_CONNECT);
			}
			break;

		case HW_VAR_MACID_SLEEP:
		{
			u32 reg_macid_sleep;
			u8 bit_shift;
			u8 id = *(u8*)val;

			if (id < 32) {
				reg_macid_sleep = REG_MACID_SLEEP;
				bit_shift = id;
			} else if (id < 64) {
				reg_macid_sleep = REG_MACID_SLEEP_1;
				bit_shift = id-32;
			} else if (id < 96) {
				reg_macid_sleep = REG_MACID_SLEEP_2;
				bit_shift = id-64;
			} else if (id < 128) {
				reg_macid_sleep = REG_MACID_SLEEP_3;
				bit_shift = id-96;
			} else {
				rtw_warn_on(1);
				break;
			}

			val32 = rtw_read32(padapter, reg_macid_sleep);
			DBG_8192C(FUNC_ADPT_FMT ": [HW_VAR_MACID_SLEEP] macid=%d, org reg_0x%03x=0x%08X\n",
				FUNC_ADPT_ARG(padapter), id, reg_macid_sleep, val32);

			if (val32 & BIT(bit_shift))
				break;

			val32 |= BIT(bit_shift);
			rtw_write32(padapter, reg_macid_sleep, val32);
		}
			break;

		case HW_VAR_MACID_WAKEUP:
		{
			u32 reg_macid_sleep;
			u8 bit_shift;
			u8 id = *(u8*)val;

			if (id < 32) {
				reg_macid_sleep = REG_MACID_SLEEP;
				bit_shift = id;
			} else if (id < 64) {
				reg_macid_sleep = REG_MACID_SLEEP_1;
				bit_shift = id-32;
			} else if (id < 96) {
				reg_macid_sleep = REG_MACID_SLEEP_2;
				bit_shift = id-64;
			} else if (id < 128) {
				reg_macid_sleep = REG_MACID_SLEEP_3;
				bit_shift = id-96;
			} else {
				rtw_warn_on(1);
				break;
			}

			val32 = rtw_read32(padapter, reg_macid_sleep);
			DBG_8192C(FUNC_ADPT_FMT ": [HW_VAR_MACID_WAKEUP] macid=%d, org reg_0x%03x=0x%08X\n",
				FUNC_ADPT_ARG(padapter), id, reg_macid_sleep, val32);

			if (!(val32 & BIT(bit_shift)))
				break;

			val32 &= ~BIT(bit_shift);
			rtw_write32(padapter, reg_macid_sleep, val32);
		}
			break;
#ifdef CONFIG_GPIO_WAKEUP
		case HW_SET_GPIO_WL_CTRL:
		{
			u8 enable = *val;
			u8 value = rtw_read8(padapter, 0x4e);
			if (enable && (value & BIT(6))) {
				value &= ~BIT(6);
				rtw_write8(padapter, 0x4e, value);
			} else if (enable == _FALSE){
				value |= BIT(6);
				rtw_write8(padapter, 0x4e, value);
			}
			DBG_871X("%s: set WL control, 0x4E=0x%02X\n",
					__func__, rtw_read8(padapter, 0x4e));
		}
			break;
#endif
		default:
			SetHwReg(padapter, variable, val);
			break;
	}
