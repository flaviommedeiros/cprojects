switch ( EncryptType )
    {
        default:
        case eCSR_ENCRYPT_TYPE_NONE:
            edType = eSIR_ED_NONE;
            break;

        case eCSR_ENCRYPT_TYPE_WEP40_STATICKEY:
        case eCSR_ENCRYPT_TYPE_WEP40:
            edType = eSIR_ED_WEP40;
            break;

        case eCSR_ENCRYPT_TYPE_WEP104_STATICKEY:
        case eCSR_ENCRYPT_TYPE_WEP104:
            edType = eSIR_ED_WEP104;
            break;

        case eCSR_ENCRYPT_TYPE_TKIP:
            edType = eSIR_ED_TKIP;
            break;

        case eCSR_ENCRYPT_TYPE_AES:
            edType = eSIR_ED_CCMP;
            break;
#ifdef FEATURE_WLAN_WAPI
        case eCSR_ENCRYPT_TYPE_WPI:
            edType = eSIR_ED_WPI;
#endif
#ifdef WLAN_FEATURE_11W
        //11w BIP
        case eCSR_ENCRYPT_TYPE_AES_CMAC:
            edType = eSIR_ED_AES_128_CMAC;
            break;
#endif
    }
