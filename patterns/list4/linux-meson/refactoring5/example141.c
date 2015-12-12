#ifdef CONFIG_AUTOSUSPEND
if(padapter->registrypriv.usbss_enable)
		{
			if(pwrpriv->rf_pwrstate == rf_on)
			{
				if(padapter->net_closed == _TRUE)
					pwrpriv->ps_flag = _TRUE;

				rfpwrstate = RfOnOffDetect(padapter);
				DBG_871X("@@@@- #1  %s==> rfstate:%s \n",__FUNCTION__,(rfpwrstate==rf_on)?"rf_on":"rf_off");
				if(rfpwrstate!= pwrpriv->rf_pwrstate)
				{
					if(rfpwrstate == rf_off)
					{
						pwrpriv->change_rfpwrstate = rf_off;
						
						pwrpriv->bkeepfwalive = _TRUE;	
						pwrpriv->brfoffbyhw = _TRUE;						
						
						autosuspend_enter(padapter);							
					}
				}
			}			
		}
		else
	#endif //CONFIG_AUTOSUSPEND
		{
			rfpwrstate = RfOnOffDetect(padapter);
			DBG_871X("@@@@- #2  %s==> rfstate:%s \n",__FUNCTION__,(rfpwrstate==rf_on)?"rf_on":"rf_off");

			if(rfpwrstate!= pwrpriv->rf_pwrstate)
			{
				if(rfpwrstate == rf_off)
				{	
					pwrpriv->change_rfpwrstate = rf_off;														
					pwrpriv->brfoffbyhw = _TRUE;
					padapter->bCardDisableWOHSM = _TRUE;
					rtw_hw_suspend(padapter );	
				}
				else
				{
					pwrpriv->change_rfpwrstate = rf_on;
					rtw_hw_resume(padapter );			
				}
				DBG_871X("current rf_pwrstate(%s)\n",(pwrpriv->rf_pwrstate == rf_off)?"rf_off":"rf_on");
			}
		}
