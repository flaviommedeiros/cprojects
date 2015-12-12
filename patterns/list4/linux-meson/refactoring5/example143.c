#ifdef CONFIG_AUTOSUSPEND
if(pwrpriv->brfoffbyhw==_TRUE)
		{
			DBG_8192C("hw still in rf_off state ...........\n");
			ret = _FAIL;
			goto exit;
		}
		else if(padapter->registrypriv.usbss_enable)
		{
			DBG_8192C("%s call autoresume_enter....\n",__FUNCTION__);
			if(_FAIL ==  autoresume_enter(padapter))
			{
				DBG_8192C("======> autoresume fail.............\n");
				ret = _FAIL;
				goto exit;
			}	
		}
		else
#endif
#endif
		{
#ifdef CONFIG_IPS
			DBG_8192C("%s call ips_leave....\n",__FUNCTION__);
			if(_FAIL ==  ips_leave(padapter))
			{
				DBG_8192C("======> ips_leave fail.............\n");
				ret = _FAIL;
				goto exit;
			}
#endif
		}
