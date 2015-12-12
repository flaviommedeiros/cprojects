switch(dot11Mode)
        {
            case WNI_CFG_DOT11_MODE_11A:
                return eSTA_11a;
            case WNI_CFG_DOT11_MODE_11B:
                return eSTA_11b;
            case WNI_CFG_DOT11_MODE_11G:
                return eSTA_11bg;
            case WNI_CFG_DOT11_MODE_11N:
                return eSTA_11n;
#ifdef WLAN_FEATURE_11AC
            case WNI_CFG_DOT11_MODE_11AC:
                return eSTA_11ac;
#endif
            case WNI_CFG_DOT11_MODE_ALL:
            default:
                return eSTA_11n;           
            
        }
