switch ( pSirBssDesc->nwType )
    {
        case eSIR_11A_NW_TYPE:
            phyMode = eCSR_DOT11_MODE_11a;
            break;

        case eSIR_11B_NW_TYPE:
            phyMode = eCSR_DOT11_MODE_11b;
            break;

        case eSIR_11G_NW_TYPE:
            phyMode = eCSR_DOT11_MODE_11g;
            break;

        case eSIR_11N_NW_TYPE:
            phyMode = eCSR_DOT11_MODE_11n;
            break;
#ifdef WLAN_FEATURE_11AC
        case eSIR_11AC_NW_TYPE:
        default:
            phyMode = eCSR_DOT11_MODE_11ac;
#else
        default:
            phyMode = eCSR_DOT11_MODE_11n;
#endif
            break;
    }
