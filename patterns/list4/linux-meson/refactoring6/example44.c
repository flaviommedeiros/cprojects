if ((_FALSE == bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
#endif
		)
	{
		sd_cmd52_read(pintfhdl, addr, 4, (u8*)&val);
		val = le32_to_cpu(val);
	}
	else
		val = sd_read32(pintfhdl, addr, NULL);
