switch (pattrib->encrypt)
		{
			// SEC_TYPE
			case _WEP40_:
			case _WEP104_:
			case _TKIP_:
			case _TKIP_WTMIC_:
				sectype = 1;
				break;

#ifdef CONFIG_WAPI_SUPPORT
			case _SMS4_:
				sectype = 2;
				break;
#endif
			case _AES_:
				sectype = 3;
				break;

			case _NO_PRIVACY_:
			default:
					break;
		}
