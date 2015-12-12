switch ( pProfile->negotiatedAuthType )
    {
        case eCSR_AUTH_TYPE_WPA:
        case eCSR_AUTH_TYPE_WPA_PSK:
        case eCSR_AUTH_TYPE_WPA_NONE:
#ifdef FEATURE_WLAN_CCX
        case eCSR_AUTH_TYPE_CCKM_WPA:
#endif
            fWpaProfile = TRUE;
            break;

        default:
            fWpaProfile = FALSE;
            break;
    }
