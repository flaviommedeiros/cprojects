switch(mode){
		case VMODE_480I:
		case VMODE_480I_RPT:
		case VMODE_480P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_480P_59HZ:// for framerate automation 480p 59.94hz
#endif
		case VMODE_480P_RPT:
		case VMODE_576I:
		case VMODE_576I_RPT:
		case VMODE_576P:
		case VMODE_576P_RPT:
		case VMODE_720P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_720P_59HZ: // for framerate automation 720p 59.94hz
#endif
		case VMODE_1080I:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_1080I_59HZ: // for framerate automation 1080i 59.94hz
#endif
		case VMODE_1080P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_1080P_59HZ: // for framerate automation 1080p 59.94hz
#endif
		case VMODE_720P_50HZ:
		case VMODE_1080I_50HZ:
		case VMODE_1080P_50HZ:
		case VMODE_1080P_24HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_1080P_23HZ: // for framerate automation 1080p 23.97hz
#endif
		case VMODE_4K2K_30HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_4K2K_29HZ: // for framerate automation 4k2k 29.97hz
#endif
		case VMODE_4K2K_25HZ:
		case VMODE_4K2K_24HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case VMODE_4K2K_23HZ: // for framerate automation 4k2k 23.97hz
#endif
		case VMODE_4K2K_SMPTE:
		case VMODE_4K2K_FAKE_5G:  // timing same as 4k2k30hz, Vsync from 30hz to 50hz
		case VMODE_4K2K_60HZ:	  // timing same as 4k2k30hz, Vsync from 30hz to 60hz
		case VMODE_4K2K_50HZ:	  // timing same as 4k2k30hz, Vsync from 30hz to 60hz
		case VMODE_4K2K_5G:
			ret=1;
			break;
		default:
			ret=0;
			break;
	}
