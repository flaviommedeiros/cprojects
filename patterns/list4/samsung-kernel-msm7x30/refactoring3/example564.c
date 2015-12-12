switch (value) {
	case SIG_MDNIE_UI_MODE:
		current_mDNIe_Mode = mDNIe_UI_MODE;
		break;

	case SIG_MDNIE_VIDEO_MODE:
		current_mDNIe_Mode = mDNIe_VIDEO_MODE;
		break;

	case SIG_MDNIE_VIDEO_WARM_MODE:
		current_mDNIe_Mode = mDNIe_VIDEO_WARM_MODE;
		break;

	case SIG_MDNIE_VIDEO_COLD_MODE:
		current_mDNIe_Mode = mDNIe_VIDEO_COLD_MODE;
		break;

	case SIG_MDNIE_CAMERA_MODE:
		current_mDNIe_Mode = mDNIe_CAMERA_MODE;
		break;

	case SIG_MDNIE_NAVI:
		current_mDNIe_Mode = mDNIe_NAVI;
		break;

	case SIG_MDNIE_GALLERY:
		current_mDNIe_Mode = mDNIe_GALLERY;
		break;

	case SIG_MDNIE_BYPASS:  
		current_mDNIe_Mode = mDNIe_BYPASS;
		break;

#if defined(CONFIG_TDMB) || defined(CONFIG_TDMB_MODULE)
	case SIG_MDNIE_DMB_MODE:
		current_mDNIe_Mode = mDNIe_DMB_MODE;
		break;

	case SIG_MDNIE_DMB_WARM_MODE:
		current_mDNIe_Mode = mDNIe_DMB_WARM_MODE;
		break;

	case SIG_MDNIE_DMB_COLD_MODE:
		current_mDNIe_Mode = mDNIe_DMB_COLD_MODE;
		break;
#endif 
#ifdef CONFIG_TARGET_LOCALE_NTT
	case SIG_MDNIE_ISDBT_MODE:
		current_mDNIe_Mode = mDNIe_ISDBT_MODE;
		break;

	case SIG_MDNIE_ISDBT_WARM_MODE:
		current_mDNIe_Mode = mDNIe_ISDBT_WARM_MODE;
		break;

	case SIG_MDNIE_ISDBT_COLD_MODE:
		current_mDNIe_Mode = mDNIe_ISDBT_COLD_MODE;
		break;
#endif
#ifdef BROWSER_COLOR_TONE_SET
	case SIG_MDNIE_BROWSER_TONE1:
		current_mDNIe_Mode = mDNIe_BROWSER_TONE1;
		break;
	case SIG_MDNIE_BROWSER_TONE2:
		current_mDNIe_Mode = mDNIe_BROWSER_TONE2;
		break;
	case SIG_MDNIE_BROWSER_TONE3:
		current_mDNIe_Mode = mDNIe_BROWSER_TONE3;
		break;		
#endif

	default:
		printk(KERN_ERR "\nscenario_store value is wrong : value(%d)\n", value);
		break;
	}
