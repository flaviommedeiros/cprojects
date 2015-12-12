switch (mode) {
		case VMODE_480I:
		case VMODE_480CVBS:
		case VMODE_576I:
		case VMODE_576CVBS:
		case VMODE_1080I:
		case VMODE_1080I_50HZ:
		#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
    		case VMODE_1080I_59HZ:
		#endif
			scan_mode = TVIN_SCAN_MODE_INTERLACED;
			break;
		case VMODE_480P:
		case VMODE_576P:
		case VMODE_720P:
		case VMODE_1080P:
		case VMODE_720P_50HZ:
		case VMODE_1080P_50HZ:
		case VMODE_1080P_24HZ:
		case VMODE_4K2K_30HZ:
		case VMODE_4K2K_25HZ:
		case VMODE_4K2K_24HZ:
		case VMODE_4K2K_SMPTE:
		case VMODE_VGA:
		case VMODE_SVGA:
		case VMODE_XGA:
		case VMODE_SXGA:
		case VMODE_LCD:
		case VMODE_LVDS_1080P:
		case VMODE_LVDS_1080P_50HZ:
		case VMODE_LVDS_768P:
	#if MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8
	#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
    case VMODE_480P_59HZ:
		case VMODE_720P_59HZ:
		case VMODE_1080P_59HZ:
		case VMODE_1080P_23HZ:
		case VMODE_4K2K_29HZ:
		case VMODE_4K2K_23HZ:
	#endif
	#endif
			scan_mode = TVIN_SCAN_MODE_PROGRESSIVE;
			break;
		default:
			printk("unknown mode=%d\n", mode);
			break;
	}
