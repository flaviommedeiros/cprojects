switch(encType)
    {
    case eCSR_ENCRYPT_TYPE_WEP40_STATICKEY:
    case eCSR_ENCRYPT_TYPE_WEP40:
        n = ENC_MODE_WEP40;
        break;
    case eCSR_ENCRYPT_TYPE_WEP104_STATICKEY:
    case eCSR_ENCRYPT_TYPE_WEP104:
        n = ENC_MODE_WEP104;
        break;
    case eCSR_ENCRYPT_TYPE_TKIP:
        n = ENC_MODE_TKIP;
        break;
    case eCSR_ENCRYPT_TYPE_AES:
        n = ENC_MODE_AES;
        break;
#ifdef FEATURE_WLAN_WAPI
    case eCSR_ENCRYPT_TYPE_WPI:
        n = ENC_MODE_SMS4;
        break;
#endif /* FEATURE_WLAN_WAPI */
    default:
        break;
    }
