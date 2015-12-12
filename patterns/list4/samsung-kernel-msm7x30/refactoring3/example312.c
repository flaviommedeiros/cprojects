switch(authType)
    {
    case eCSR_AUTH_TYPE_SHARED_KEY:
        n = AUTH_SHARED;
        break;
    case eCSR_AUTH_TYPE_WPA:
        n = AUTH_WPA_EAP;
        break;
    case eCSR_AUTH_TYPE_WPA_PSK:
        n = AUTH_WPA_PSK;
        break;
    case eCSR_AUTH_TYPE_RSN:
        n = AUTH_WPA2_EAP;
        break;
    case eCSR_AUTH_TYPE_RSN_PSK:
        n = AUTH_WPA2_PSK;
        break;
#ifdef FEATURE_WLAN_WAPI
    case eCSR_AUTH_TYPE_WAPI_WAI_CERTIFICATE:
        n = AUTH_WAPI_CERT;
        break;
    case eCSR_AUTH_TYPE_WAPI_WAI_PSK:
        n = AUTH_WAPI_PSK;
        break;
#endif /* FEATURE_WLAN_WAPI */
    default:
        break;
    }
