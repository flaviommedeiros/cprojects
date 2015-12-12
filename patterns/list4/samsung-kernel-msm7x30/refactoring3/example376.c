switch (cipher) 
        {
            case IW_AUTH_CIPHER_NONE:
                encryptionType = eCSR_ENCRYPT_TYPE_NONE;
                break;
    
            case WLAN_CIPHER_SUITE_WEP40:
                if ((IW_AUTH_KEY_MGMT_802_1X == pWextState->authKeyMgmt) && 
                    (eCSR_AUTH_TYPE_OPEN_SYSTEM == pHddStaCtx->conn_info.authType))
                    encryptionType = eCSR_ENCRYPT_TYPE_WEP40;
                else
                    encryptionType = eCSR_ENCRYPT_TYPE_WEP40_STATICKEY;
                break;
    
            case WLAN_CIPHER_SUITE_WEP104:
                if ((IW_AUTH_KEY_MGMT_802_1X == pWextState->authKeyMgmt) && 
                    (eCSR_AUTH_TYPE_OPEN_SYSTEM == pHddStaCtx->conn_info.authType))
                    encryptionType = eCSR_ENCRYPT_TYPE_WEP104;
                else
                    encryptionType = eCSR_ENCRYPT_TYPE_WEP104_STATICKEY;
                break;
    
            case WLAN_CIPHER_SUITE_TKIP:
                encryptionType = eCSR_ENCRYPT_TYPE_TKIP;
                break;
    
            case WLAN_CIPHER_SUITE_CCMP:
                encryptionType = eCSR_ENCRYPT_TYPE_AES;
                break;
#ifdef FEATURE_WLAN_WAPI
        case WLAN_CIPHER_SUITE_SMS4:
            encryptionType = eCSR_ENCRYPT_TYPE_WPI;
            break;
#endif

#ifdef FEATURE_WLAN_CCX
        case WLAN_CIPHER_SUITE_KRK:
            encryptionType = eCSR_ENCRYPT_TYPE_KRK;
            break;
#endif
            default:
                hddLog(VOS_TRACE_LEVEL_ERROR, "%s: Unsupported cipher type %d", 
                        __func__, cipher);
                return -EOPNOTSUPP;
        }
