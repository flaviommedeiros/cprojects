#ifdef CONFIG_AML_GPIO_KEY
if (det_pwr_key())//get pwr key and wakeup im
	{
		clr_pwr_key();
		WRITE_AOBUS_REG(AO_RTI_STATUS_REG2, FLAG_WAKEUP_PWRKEY);
	} else
#endif
        {
#ifdef CONFIG_MESON_SUSPEND
#ifdef CONFIG_MESON_TRUSTZONE
		meson_suspend_firmware();
#else
		meson_power_suspend();
#endif
#else
#if 0
		//k101 power key
		aml_set_reg32_mask(P_AO_GPIO_O_EN_N, (1 << 3));
		aml_set_reg32_mask(P_AO_RTI_PULL_UP_REG, (1 << 3)|(1<<19));
		do {
			udelay(1000);
		}while((aml_read_reg32(P_AO_GPIO_I)&(1<<3)));
#endif
#endif
	}
