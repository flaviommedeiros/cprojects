#ifdef DBG_CONFIG_ERROR_DETECT
if (psrtpriv->silent_reset_inprogress == _TRUE)
#endif//#ifdef DBG_CONFIG_ERROR_DETECT		
#endif //defined(CONFIG_SWLPS_IN_IPS) || defined(CONFIG_FWLPS_IN_IPS)
		rtw_reset_drv_sw(padapter);
