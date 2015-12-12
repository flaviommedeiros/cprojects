switch (vmode) {
	case VMODE_480I:
	case VMODE_480CVBS:
	case VMODE_576I:
	case VMODE_576CVBS:
	case VMODE_1080I:
	case VMODE_1080I_50HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
	case VMODE_1080I_59HZ:
#endif
		osd_need_antiflicker = false;
		break;
	default:
		break;
	}
