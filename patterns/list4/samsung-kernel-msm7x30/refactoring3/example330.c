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
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;
                break;
#ifdef WLAN_FEATURE_11AC
            case eCSR_DOT11_MODE_11ac:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11AC;
                break;
#endif
            case eCSR_DOT11_MODE_TAURUS:
            default:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_TAURUS;
                break;
            }
