if ((padapter->bSurpriseRemoved == _TRUE)
			|| (padapter->hw_init_completed == _FALSE)
#ifdef CONFIG_USB_HCI
			|| (padapter->bDriverStopped== _TRUE)
#endif
			|| (pwrpriv->pwr_mode == PS_MODE_ACTIVE)
			)
		{
			bReady = _TRUE;
		}
