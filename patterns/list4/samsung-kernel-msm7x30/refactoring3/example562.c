switch (current_mDNIe_Mode) {
	case mDNIe_UI_MODE:
	default:
		mdnie_ui = 0;
		break;

	case mDNIe_VIDEO_MODE:
		mdnie_ui = 1;
		break;

	case mDNIe_VIDEO_WARM_MODE:
		mdnie_ui = 2;
		break;

	case mDNIe_VIDEO_COLD_MODE:
		mdnie_ui = 3;
		break;

	case mDNIe_CAMERA_MODE:
		mdnie_ui = 4;
		break;

	case mDNIe_NAVI:
		mdnie_ui = 5;
		break;

	case mDNIe_GALLERY:
		mdnie_ui = 6;
		break;

	case mDNIe_BYPASS:  
		mdnie_ui = 7;
		break;
		
#if defined(CONFIG_TDMB) || defined(CONFIG_TDMB_MODULE)
	case mDNIe_DMB_MODE:
		mdnie_ui = mDNIe_DMB_MODE;
		break;

	case mDNIe_DMB_WARM_MODE:
		mdnie_ui = mDNIe_DMB_WARM_MODE;
		break;

	case mDNIe_DMB_COLD_MODE:
		mdnie_ui = mDNIe_DMB_COLD_MODE;
		break;
#endif
#ifdef CONFIG_TARGET_LOCALE_NTT
	case mDNIe_ISDBT_MODE:
		mdnie_ui = mDNIe_ISDBT_MODE;
		break;

	case mDNIe_ISDBT_WARM_MODE:
		mdnie_ui = mDNIe_ISDBT_WARM_MODE;
		break;

	case mDNIe_ISDBT_COLD_MODE:
		mdnie_ui = mDNIe_ISDBT_COLD_MODE;
		break;
#endif
#ifdef BROWSER_COLOR_TONE_SET
	case mDNIe_BROWSER_TONE1:
		mdnie_ui = mDNIe_BROWSER_TONE1;
		break;
	case mDNIe_BROWSER_TONE2:
		mdnie_ui = mDNIe_BROWSER_TONE2;
		break;
	case mDNIe_BROWSER_TONE3:
		mdnie_ui = mDNIe_BROWSER_TONE3;
		break;
#endif		
	}
