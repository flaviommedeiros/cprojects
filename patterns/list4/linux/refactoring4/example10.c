# ifndef CONFIG_SDH_BFIN_MISSING_CMD_PULLUP_WORKAROUND
if (ios->power_mode != MMC_POWER_OFF)
		pwr_ctl |= PWR_ON;
	else
		pwr_ctl &= ~PWR_ON;
