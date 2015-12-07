#ifdef OSEN
if (!bcmp(akm, WFA_OUI, WFA_OUI_LEN)) {
		switch (akm[WFA_OUI_LEN]) {
		case OSEN_AKM_UNSPECIFIED:
			*auth = WPA2_AUTH_UNSPECIFIED;
			break;

		default:
			return FALSE;
		}
		return TRUE;
	}
	else
#endif	/* OSEN */
	if (!bcmp(akm, WPA_OUI, DOT11_OUI_LEN)) {
		switch (akm[DOT11_OUI_LEN]) {
		case RSN_AKM_NONE:
			*auth = WPA_AUTH_NONE;
			break;
		case RSN_AKM_UNSPECIFIED:
			*auth = WPA_AUTH_UNSPECIFIED;
			break;
		case RSN_AKM_PSK:
			*auth = WPA_AUTH_PSK;
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
