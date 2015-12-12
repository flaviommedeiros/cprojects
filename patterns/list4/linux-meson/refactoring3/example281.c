switch (cipher) {
	case IW_AUTH_CIPHER_NONE:
		*profile_cipher = _NO_PRIVACY_;
		ndisencryptstatus = Ndis802_11EncryptionDisabled;
#ifdef CONFIG_WAPI_SUPPORT
		if(psecuritypriv->dot11PrivacyAlgrthm ==_SMS4_ )
		{
			*profile_cipher = _SMS4_;
		}
#endif
		break;
	case WLAN_CIPHER_SUITE_WEP40:
		*profile_cipher = _WEP40_;
		ndisencryptstatus = Ndis802_11Encryption1Enabled;
		break;
	case WLAN_CIPHER_SUITE_WEP104:
		*profile_cipher = _WEP104_;
		ndisencryptstatus = Ndis802_11Encryption1Enabled;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		*profile_cipher = _TKIP_;
		ndisencryptstatus = Ndis802_11Encryption2Enabled;
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		*profile_cipher = _AES_;
		ndisencryptstatus = Ndis802_11Encryption3Enabled;
		break;
#ifdef CONFIG_WAPI_SUPPORT
	case WLAN_CIPHER_SUITE_SMS4:
		*profile_cipher = _SMS4_;
		ndisencryptstatus = Ndis802_11_EncrypteionWAPI;
		break;
#endif
	default:
		DBG_8192C("Unsupported cipher: 0x%x\n", cipher);
		return -ENOTSUPP;
	}
