#ifdef CONFIG_DRVEXT_MODULE
if(padapter->drvextpriv.enable_wpa)
		{
			indicate_l2_connect(padapter);
		}
		else
#endif
		{
			rtw_os_indicate_connect(padapter);
		}
