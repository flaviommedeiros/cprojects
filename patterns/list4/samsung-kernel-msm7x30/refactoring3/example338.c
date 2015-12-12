switch(phyMode)
    {
    case eCSR_DOT11_MODE_11a:
    case eCSR_DOT11_MODE_11a_ONLY:
        cfgDot11Mode = eCSR_CFG_DOT11_MODE_11A;
        break;
    case eCSR_DOT11_MODE_11b:
    case eCSR_DOT11_MODE_11b_ONLY:
        cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
        break;
    case eCSR_DOT11_MODE_11g:
    case eCSR_DOT11_MODE_11g_ONLY:
#ifdef WLAN_SOFTAP_FEATURE
        if(pProfile && (CSR_IS_INFRA_AP(pProfile)) && (phyMode == eCSR_DOT11_MODE_11g_ONLY))
            cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G_ONLY;
        else
#endif
        cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G;
        break;
    case eCSR_DOT11_MODE_11n:
        if(fProprietary)
        {
            cfgDot11Mode = eCSR_CFG_DOT11_MODE_TAURUS;
        }
        else
        {
            cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;
        }
        break;
    case eCSR_DOT11_MODE_11n_ONLY:
#ifdef WLAN_SOFTAP_FEATURE
       if(pProfile && CSR_IS_INFRA_AP(pProfile))
           cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N_ONLY;
       else
#endif
       cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;
       break;
    case eCSR_DOT11_MODE_TAURUS:
        cfgDot11Mode = eCSR_CFG_DOT11_MODE_TAURUS;
        break;
    case eCSR_DOT11_MODE_abg:
        cfgDot11Mode = eCSR_CFG_DOT11_MODE_ABG;
        break;
    case eCSR_DOT11_MODE_AUTO:
        cfgDot11Mode = eCSR_CFG_DOT11_MODE_AUTO;
        break;

#ifdef WLAN_FEATURE_11AC
    case eCSR_DOT11_MODE_11ac:
	if (!WDA_getFwWlanFeatCaps(DOT11AC))
	{
		cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;
	}
	else
	{
		cfgDot11Mode = eCSR_CFG_DOT11_MODE_11AC;
	}
        break;
    case eCSR_DOT11_MODE_11ac_ONLY:
        cfgDot11Mode = eCSR_CFG_DOT11_MODE_11AC_ONLY;
        break;
#endif
    default:
        //No need to assign anything here
        break;
    }
