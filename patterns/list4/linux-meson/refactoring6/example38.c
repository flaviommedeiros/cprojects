if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (_FALSE == bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
#endif
		)
	{
		err = sd_cmd52_read(pintfhdl, ftaddr, cnt, pbuf);
		return err;
	}
