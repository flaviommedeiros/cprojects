#ifdef CONFIG_LPS_RPWM_TIMER
if (pwrpriv->brpwmtimeout == _TRUE)
	{
		DBG_871X("%s: RPWM timeout, force to set RPWM(0x%02X) again!\n", __FUNCTION__, pslv);
	}
	else
#endif // CONFIG_LPS_RPWM_TIMER
	{
		if ( (pwrpriv->rpwm == pslv)
#ifdef CONFIG_LPS_LCLK
			|| ((pwrpriv->rpwm >= PS_STATE_S2)&&(pslv >= PS_STATE_S2))
#endif
			)
		{
			RT_TRACE(_module_rtl871x_pwrctrl_c_,_drv_err_,
				("%s: Already set rpwm[0x%02X], new=0x%02X!\n", __FUNCTION__, pwrpriv->rpwm, pslv));
			return;
		}
	}
