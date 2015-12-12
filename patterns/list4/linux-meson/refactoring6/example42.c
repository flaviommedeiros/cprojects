if ((_FALSE == bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
#endif
		)
	{
		err = _sd_cmd52_write(pintfhdl, addr, cnt, pbuf);
		return err;
	}
