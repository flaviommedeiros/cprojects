switch ( enType )
        {
            case eCSR_ENCRYPT_TYPE_WEP40:
            case eCSR_ENCRYPT_TYPE_WEP40_STATICKEY:
                OUIIndex = CSR_OUI_WEP40_OR_1X_INDEX;
                break;
            case eCSR_ENCRYPT_TYPE_WEP104:
            case eCSR_ENCRYPT_TYPE_WEP104_STATICKEY:
                OUIIndex = CSR_OUI_WEP104_INDEX;
                break;
            case eCSR_ENCRYPT_TYPE_TKIP:
                OUIIndex = CSR_OUI_TKIP_OR_PSK_INDEX;
                break;
            case eCSR_ENCRYPT_TYPE_AES:
                OUIIndex = CSR_OUI_AES_INDEX;
                break;
            case eCSR_ENCRYPT_TYPE_NONE:
                OUIIndex = CSR_OUI_USE_GROUP_CIPHER_INDEX;
                break;
#ifdef FEATURE_WLAN_WAPI
           case eCSR_ENCRYPT_TYPE_WPI:
               OUIIndex = CSR_OUI_WAPI_WAI_CERT_OR_SMS4_INDEX;
               break;
#endif /* FEATURE_WLAN_WAPI */
            default: //HOWTO handle this?
                OUIIndex = CSR_OUI_RESERVED_INDEX;
                break;
        }
