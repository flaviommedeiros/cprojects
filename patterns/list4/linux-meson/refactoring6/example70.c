if ((check_fwstate(pmlmepriv, _FW_LINKED) == _TRUE)
#ifdef CONFIG_CONCURRENT_MODE
		|| (check_buddy_fwstate(Adapter,_FW_LINKED) == _TRUE)
#endif
		)
	{ //connect

		if(pwrpriv->pwr_mode == PS_MODE_ACTIVE) {
			DBG_871X("%s: Driver Already Leave LPS\n",__FUNCTION__);
			return;
		}

#ifdef CONFIG_LPS_LCLK
		_enter_pwrlock(&pwrpriv->lock);

#ifndef CONFIG_DETECT_CPWM_BY_POLLING
		cpwm_orig = 0;
		rtw_hal_get_hwreg(Adapter, HW_VAR_CPWM, &cpwm_orig);
#endif //CONFIG_DETECT_CPWM_BY_POLLING
		rtw_set_rpwm(Adapter, PS_STATE_S4);

#ifndef CONFIG_DETECT_CPWM_BY_POLLING

		start_time = rtw_get_current_time();

		// polling cpwm
		do {
			rtw_mdelay_os(1);

			rtw_hal_get_hwreg(Adapter, HW_VAR_CPWM, &cpwm_now);
			if ((cpwm_orig ^ cpwm_now) & 0x80)
			{
				pwrpriv->cpwm = PS_STATE_S4;
				pwrpriv->cpwm_tog = cpwm_now & PS_TOGGLE;
#ifdef DBG_CHECK_FW_PS_STATE
				DBG_871X("%s: polling cpwm OK! cpwm_orig=%02x, cpwm_now=%02x, 0x100=0x%x \n"
				, __FUNCTION__, cpwm_orig, cpwm_now, rtw_read8(Adapter, REG_CR));
				if(rtw_fw_ps_state(Adapter) == _FAIL)
				{
					DBG_871X("%s: leave 32k but fw state in 32k\n", __FUNCTION__);
					pdbgpriv->dbg_rpwm_toogle_cnt++;
				}
#endif //DBG_CHECK_FW_PS_STATE
				break;
			}

			if (rtw_get_passing_time_ms(start_time) > LPS_RPWM_WAIT_MS)
			{
				DBG_871X("%s: polling cpwm timeout! cpwm_orig=%02x, cpwm_now=%02x \n", __FUNCTION__, cpwm_orig, cpwm_now);
#ifdef DBG_CHECK_FW_PS_STATE
				if(rtw_fw_ps_state(Adapter) == _FAIL)
				{
					DBG_871X("rpwm timeout and fw ps state in 32k\n");
					pdbgpriv->dbg_rpwm_timeout_fail_cnt++;
				}
#endif //DBG_CHECK_FW_PS_STATE
				break;
			}
		} while (1);
#endif // CONFIG_DETECT_CPWM_BY_POLLING

	_exit_pwrlock(&pwrpriv->lock);
#endif

#ifdef CONFIG_P2P_PS
		p2p_ps_wk_cmd(pri_padapter, P2P_PS_DISABLE, 0);
#endif //CONFIG_P2P_PS

#ifdef CONFIG_LPS
		rtw_lps_ctrl_wk_cmd(pri_padapter, LPS_CTRL_LEAVE, 0);
#endif
	}
	else
	{
		if(pwrpriv->rf_pwrstate== rf_off)
		{
			#ifdef CONFIG_AUTOSUSPEND
			if(Adapter->registrypriv.usbss_enable)
			{
				#if (LINUX_VERSION_CODE>=KERNEL_VERSION(2,6,35))
				usb_disable_autosuspend(adapter_to_dvobj(Adapter)->pusbdev);
				#elif (LINUX_VERSION_CODE>=KERNEL_VERSION(2,6,22) && LINUX_VERSION_CODE<=KERNEL_VERSION(2,6,34))
				adapter_to_dvobj(Adapter)->pusbdev->autosuspend_disabled = Adapter->bDisableAutosuspend;//autosuspend disabled by the user
				#endif
			}
			else
			#endif
			{
#if defined(CONFIG_FWLPS_IN_IPS) || defined(CONFIG_SWLPS_IN_IPS) || defined(CONFIG_RTL8188E)
				#ifdef CONFIG_IPS
				if(_FALSE == ips_leave(pri_padapter))
				{
					DBG_871X("======> ips_leave fail.............\n");			
				}
				#endif
#endif //CONFIG_SWLPS_IN_IPS || (CONFIG_PLATFORM_SPRD && CONFIG_RTL8188E)
			}
		}
	}
