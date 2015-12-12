switch ( pProfile->negotiatedAuthType )
    {
        case eCSR_AUTH_TYPE_RSN:
        case eCSR_AUTH_TYPE_RSN_PSK:
#ifdef WLAN_FEATURE_VOWIFI_11R
        case eCSR_AUTH_TYPE_FT_RSN:
        case eCSR_AUTH_TYPE_FT_RSN_PSK:
#endif 
#ifdef FEATURE_WLAN_CCX
        case eCSR_AUTH_TYPE_CCKM_RSN:
#endif 
            fRSNProfile = TRUE;
            break;

        default:
            fRSNProfile = FALSE;
            break;
    }
