switch( phyModeIn )
    {
        case eCSR_DOT11_MODE_abg:   //11a or 11b or 11g
            if( f5GhzBand )
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11A;
            }
            else if( eCSR_DOT11_MODE_11b == bssPhyMode )
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
            }
            else
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G;
            }
            break;

        case eCSR_DOT11_MODE_11a:   //11a
            if( f5GhzBand )
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11A;
            }
            break;

        case eCSR_DOT11_MODE_11a_ONLY:   //11a
            if( eCSR_DOT11_MODE_11a == bssPhyMode )
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11A;
            }
            break;

        case eCSR_DOT11_MODE_11g:
            if(!f5GhzBand)
            {
                if( eCSR_DOT11_MODE_11b == bssPhyMode )
                {
                    fMatch = TRUE;
                    cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
                }
                else
                {
                    fMatch = TRUE;
                    cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G;
                }
            }
            break;

        case eCSR_DOT11_MODE_11g_ONLY:
            if( eCSR_DOT11_MODE_11g == bssPhyMode )
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11G;
            }
            break;

        case eCSR_DOT11_MODE_11b:
            if( !f5GhzBand )
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
            }
            break;

        case eCSR_DOT11_MODE_11b_ONLY:
            if( eCSR_DOT11_MODE_11b == bssPhyMode )
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11B;
            }
            break;

        case eCSR_DOT11_MODE_11n:
            fMatch = TRUE;
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
            break;

        case eCSR_DOT11_MODE_11n_ONLY:
            if((eCSR_DOT11_MODE_11n == bssPhyMode) || (eCSR_DOT11_MODE_TAURUS == bssPhyMode))
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11N;

            }

            break;
#ifdef WLAN_FEATURE_11AC
        case eCSR_DOT11_MODE_11ac:
            fMatch = TRUE;
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
            case eCSR_DOT11_MODE_11ac:
            case eCSR_DOT11_MODE_TAURUS:
            default:
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11AC;
                break;
            }
            break;

        case eCSR_DOT11_MODE_11ac_ONLY:
            if((eCSR_DOT11_MODE_11ac == bssPhyMode) || (eCSR_DOT11_MODE_TAURUS == bssPhyMode))
            {
                fMatch = TRUE;
                cfgDot11Mode = eCSR_CFG_DOT11_MODE_11AC;
            }
            break;
#endif

        case eCSR_DOT11_MODE_TAURUS:
        default:
            fMatch = TRUE;
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
            break;
    }
