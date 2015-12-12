if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (_FALSE == bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
#endif
		)
	{
		val = cpu_to_le32(val);
		err = sd_cmd52_write(pintfhdl, ftaddr, 4, (u8*)&val);
		return err;
	}
