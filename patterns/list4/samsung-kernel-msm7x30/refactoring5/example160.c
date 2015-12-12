#ifdef WLAN_SOFTAP_FEATURE
if(psessionEntry->limSystemRole == eLIM_AP_ROLE )
          retVal = psessionEntry->htOperMode;
      else
#endif
          retVal = pMac->lim.gHTOperMode;
