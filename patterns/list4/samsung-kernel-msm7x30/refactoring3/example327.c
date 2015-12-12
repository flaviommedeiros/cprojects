switch(csrDot11Mode)
    {
    case eCSR_CFG_DOT11_MODE_AUTO:
        smsLog(pMac, LOGW, FL("  Warning: sees eCSR_CFG_DOT11_MODE_AUTO \n"));
        //We cannot decide until now.
        if(pMac->roam.configParam.ProprietaryRatesEnabled)
        {
            ret = WNI_CFG_DOT11_MODE_TAURUS;
        }
        else
        {
            ret = WNI_CFG_DOT11_MODE_11N;
        }
        break;
    case eCSR_CFG_DOT11_MODE_TAURUS:
        ret = WNI_CFG_DOT11_MODE_TAURUS;
        break;
    case eCSR_CFG_DOT11_MODE_11A:
        ret = WNI_CFG_DOT11_MODE_11A;
        break;
    case eCSR_CFG_DOT11_MODE_11B:
        ret = WNI_CFG_DOT11_MODE_11B;
        break;
    case eCSR_CFG_DOT11_MODE_11G:
        ret = WNI_CFG_DOT11_MODE_11G;
        break;
    case eCSR_CFG_DOT11_MODE_11N:
        ret = WNI_CFG_DOT11_MODE_11N;
        break;
    case eCSR_CFG_DOT11_MODE_POLARIS:
        ret = WNI_CFG_DOT11_MODE_POLARIS;
        break;
    case eCSR_CFG_DOT11_MODE_TITAN:
        ret = WNI_CFG_DOT11_MODE_TITAN;
        break;
#ifdef WLAN_SOFTAP_FEATURE
    case eCSR_CFG_DOT11_MODE_11G_ONLY:
       ret = WNI_CFG_DOT11_MODE_11G_ONLY;
       break;
    case eCSR_CFG_DOT11_MODE_11N_ONLY:
       ret = WNI_CFG_DOT11_MODE_11N_ONLY;
       break;
#endif

#ifdef WLAN_FEATURE_11AC
     case eCSR_CFG_DOT11_MODE_11AC_ONLY:
        ret = WNI_CFG_DOT11_MODE_11AC_ONLY;
        break;
     case eCSR_CFG_DOT11_MODE_11AC:
        ret = WNI_CFG_DOT11_MODE_11AC;
       break;
#endif
    default:
        smsLog(pMac, LOGW, FL("doesn't expect %d as csrDo11Mode\n"), csrDot11Mode);
        if(eCSR_BAND_24 == pMac->roam.configParam.eBand)
        {
            ret = WNI_CFG_DOT11_MODE_11G;
        }
        else
        {
            ret = WNI_CFG_DOT11_MODE_11A;
        }
        break;
    }
