switch (psecuritypriv->dot11PrivacyAlgrthm)
	{
		case _WEP40_:
		case _WEP104_:
			EncryptionHeadOverhead = 4;
			break;
		case _TKIP_:
			EncryptionHeadOverhead = 8;	
			break;			
		case _AES_:
			EncryptionHeadOverhead = 8;
			break;
#ifdef CONFIG_WAPI_SUPPORT
		case _SMS4_:
			EncryptionHeadOverhead = 18;
			break;
#endif			
		default:
			EncryptionHeadOverhead = 0;
	}
