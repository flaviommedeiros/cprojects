switch (auth_type) 
    {
        case NL80211_AUTHTYPE_OPEN_SYSTEM:
        case NL80211_AUTHTYPE_AUTOMATIC:
            hddLog(VOS_TRACE_LEVEL_INFO, 
                    "%s: set authentication type to OPEN", __func__);
            pHddStaCtx->conn_info.authType = eCSR_AUTH_TYPE_OPEN_SYSTEM;
            break;

        case NL80211_AUTHTYPE_SHARED_KEY:
            hddLog(VOS_TRACE_LEVEL_INFO, 
                    "%s: set authentication type to SHARED", __func__);
            pHddStaCtx->conn_info.authType = eCSR_AUTH_TYPE_SHARED_KEY;
            break;
#ifdef FEATURE_WLAN_CCX
        case NL80211_AUTHTYPE_NETWORK_EAP:
            hddLog(VOS_TRACE_LEVEL_INFO, 
                            "%s: set authentication type to CCKM WPA", __func__);
            pHddStaCtx->conn_info.authType = eCSR_AUTH_TYPE_CCKM_WPA;//eCSR_AUTH_TYPE_CCKM_RSN needs to be handled as well if required.
            break;
#endif


        default:
            hddLog(VOS_TRACE_LEVEL_ERROR, 
                    "%s: Unsupported authentication type %d", __func__, 
                    auth_type);
            pHddStaCtx->conn_info.authType = eCSR_AUTH_TYPE_UNKNOWN;
            return -EINVAL;
    }
