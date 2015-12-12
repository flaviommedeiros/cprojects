if ((_FALSE == bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
#endif
		)
	{
		err = sd_cmd52_read(pintfhdl, addr, cnt, pbuf);
		return err;
	}
