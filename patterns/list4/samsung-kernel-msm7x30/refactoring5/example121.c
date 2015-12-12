#ifdef WLAN_FEATURE_11AC
if ( (0 == phyMode) || (eCSR_DOT11_MODE_AUTO & phyMode) || (eCSR_DOT11_MODE_TAURUS & phyMode)
       ||(eCSR_DOT11_MODE_11ac & phyMode))
    {
        cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11AC;
    }
    else
#endif

    if ( (0 == phyMode) || (eCSR_DOT11_MODE_AUTO & phyMode) || (eCSR_DOT11_MODE_TAURUS & phyMode))
    {
        cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11N;
    }
    else
    {
        if( ( eCSR_DOT11_MODE_11n | eCSR_DOT11_MODE_11n_ONLY ) & phyMode )
        {
            cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11N;
        }
        else if ( eCSR_DOT11_MODE_abg & phyMode )
        {
            if( eCSR_BAND_24 != eBand )
            {
                cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11A;
            }
            else
            {
                cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11G;
            }
        }
        else if( ( eCSR_DOT11_MODE_11a | eCSR_DOT11_MODE_11a_ONLY ) & phyMode )
        {
            cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11A;
        }
        else if( ( eCSR_DOT11_MODE_11g | eCSR_DOT11_MODE_11g_ONLY ) & phyMode )
        {
            cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11G;
        }
        else
        {
            cfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11B;
        }
    }
