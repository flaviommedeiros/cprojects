#ifdef CONFIG_BT_COEXIST
if (check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE) == _TRUE)
			{
				rtl8723b_download_BTCoex_AP_mode_rsvd_page(padapter);
			}
			else
#endif // CONFIG_BT_COEXIST
			{
				rtl8723b_download_rsvd_page(padapter, RT_MEDIA_CONNECT);
			}
