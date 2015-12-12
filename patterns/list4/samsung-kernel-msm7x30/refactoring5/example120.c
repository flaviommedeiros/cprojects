#ifdef WLAN_FEATURE_11AC
if(cfgDot11Mode == eCSR_CFG_DOT11_MODE_11AC && !WDA_getFwWlanFeatCaps(DOT11AC))
        {
            *pCfgDot11ModeToUse = eCSR_CFG_DOT11_MODE_11N;
        }
        else
#endif
        {
            *pCfgDot11ModeToUse = cfgDot11Mode;
        }
