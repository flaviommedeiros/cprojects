switch (data->flags & IW_AUTH_INDEX) {
        case IW_AUTH_WPA_VERSION:
	     /*need to support wpa2 here*/
		//printk("wpa version:%x\n", data->value);
		break;
        case IW_AUTH_CIPHER_PAIRWISE:
        case IW_AUTH_CIPHER_GROUP:
        case IW_AUTH_KEY_MGMT:
                /*
 *                  * Host AP driver does not use these parameters and allows
 *                                   * wpa_supplicant to control them internally.
 *                                                    */
                break;
        case IW_AUTH_TKIP_COUNTERMEASURES:
                ieee->tkip_countermeasures = data->value;
                break;
        case IW_AUTH_DROP_UNENCRYPTED:
                ieee->drop_unencrypted = data->value;
		break;

	case IW_AUTH_80211_AUTH_ALG:
		ieee->open_wep = (data->value&IW_AUTH_ALG_OPEN_SYSTEM)?1:0;
		//printk("open_wep:%d\n", ieee->open_wep);
		break;

#if 1
	case IW_AUTH_WPA_ENABLED:
		ieee->wpa_enabled = (data->value)?1:0;
		//printk("enable wpa:%d\n", ieee->wpa_enabled);
		break;

#endif
	case IW_AUTH_RX_UNENCRYPTED_EAPOL:
                ieee->ieee802_1x = data->value;
		break;
	case IW_AUTH_PRIVACY_INVOKED:
		ieee->privacy_invoked = data->value;
		break;
	default:
                return -EOPNOTSUPP;
	}
