#ifdef CONFIG_PLATFORM_INTEL_BYT
if(0)
#else
		if(pwrpriv->wowlan_mode || pwrpriv->wowlan_ap_mode)
#endif
		{
			rtw_resume_lock_suspend();			
			ret = rtw_resume_process(padapter);
			rtw_resume_unlock_suspend();
		}
		else
		{
#ifdef CONFIG_RESUME_IN_WORKQUEUE
			rtw_resume_in_workqueue(pwrpriv);
#else			
			if (rtw_is_earlysuspend_registered(pwrpriv))
			{
				/* jeff: bypass resume here, do in late_resume */
				rtw_set_do_late_resume(pwrpriv, _TRUE);
			}	
			else
			{
				rtw_resume_lock_suspend();			
				ret = rtw_resume_process(padapter);
				rtw_resume_unlock_suspend();
			}
#endif
		}
