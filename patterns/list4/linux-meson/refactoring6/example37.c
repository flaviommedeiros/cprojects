if (((deviceId == WLAN_IOREG_DEVICE_ID) && (offset < 0x100))
		|| (_FALSE == bMacPwrCtrlOn)
#ifdef CONFIG_LPS_LCLK
		|| (_TRUE == adapter_to_pwrctl(padapter)->bFwCurrentInPSMode)
#endif
		)
	{
		val = 0;
		err = sd_cmd52_read(pintfhdl, ftaddr, 4, (u8*)&val);
#ifdef SDIO_DEBUG_IO
		if (!err) {
#endif
			val = le32_to_cpu(val);
			return val;
#ifdef SDIO_DEBUG_IO
		}

		DBG_8192C(KERN_ERR "%s: Mac Power off, Read FAIL(%d)! addr=0x%x\n", __func__, err, addr);
		return SDIO_ERR_VAL32;
#endif
	}
