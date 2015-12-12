switch(bssPhyMode)
            {
            case eCSR_DOT11_MODE_11g:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G;
                break;
            case eCSR_DOT11_MODE_11b:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
                break;
            case eCSR_DOT11_MODE_11a:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11A;
                break;
            case eCSR_DOT11_MODE_11n:
#ifdef WLAN_FEATURE_11AC
            case eCSR_DOT11_MODE_11ac:
#endif
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;
                break;

            case eCSR_DOT11_MODE_TAURUS:
            default:
#ifdef WLAN_FEATURE_11AC
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11AC;
#else
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;
#endif
                break;
            }
