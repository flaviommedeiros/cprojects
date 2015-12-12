switch(pMac->roam.configParam.phyMode)
        {
        case eCSR_DOT11_MODE_11b:
            fAllowed = (tANI_BOOLEAN)(eCSR_DOT11_MODE_11a != phyMode);
            break;
        case eCSR_DOT11_MODE_11g:
            fAllowed = (tANI_BOOLEAN)(eCSR_DOT11_MODE_11a != phyMode);
            break;
        case eCSR_DOT11_MODE_11g_ONLY:
            fAllowed = (tANI_BOOLEAN)(eCSR_DOT11_MODE_11g == phyMode);
            break;
        case eCSR_DOT11_MODE_11a:
            fAllowed = (tANI_BOOLEAN)((eCSR_DOT11_MODE_11b != phyMode) && (eCSR_DOT11_MODE_11g != phyMode));
            break;
        case eCSR_DOT11_MODE_11n_ONLY:
            fAllowed = (tANI_BOOLEAN)((eCSR_DOT11_MODE_11n == phyMode) || (eCSR_DOT11_MODE_TAURUS == phyMode));
            break;

#ifdef WLAN_FEATURE_11AC
         case eCSR_DOT11_MODE_11ac_ONLY:
             fAllowed = (tANI_BOOLEAN)((eCSR_DOT11_MODE_11ac == phyMode) || (eCSR_DOT11_MODE_TAURUS == phyMode));
             break;
#endif
        case eCSR_DOT11_MODE_11b_ONLY:
            fAllowed = (tANI_BOOLEAN)(eCSR_DOT11_MODE_11b == phyMode);
            break;
        case eCSR_DOT11_MODE_11a_ONLY:
            fAllowed = (tANI_BOOLEAN)(eCSR_DOT11_MODE_11a == phyMode);
            break;
        case eCSR_DOT11_MODE_11n:
#ifdef WLAN_FEATURE_11AC
        case eCSR_DOT11_MODE_11ac:
#endif
        case eCSR_DOT11_MODE_TAURUS:
        default:
            fAllowed = eANI_BOOLEAN_TRUE;
            break;
        }
