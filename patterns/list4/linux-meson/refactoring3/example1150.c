switch (vmod) {
			case VMODE_480P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
			case VMODE_480P_59HZ:
#endif
            case VMODE_480P_RPT:
			case VMODE_576P:
			case VMODE_576P_RPT:
			case VMODE_720P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
			case VMODE_720P_59HZ:
#endif
			case VMODE_1080I:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
			case VMODE_1080I_59HZ:
#endif
			case VMODE_1080P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
			case VMODE_1080P_59HZ:
#endif
			case VMODE_720P_50HZ:
			case VMODE_1080I_50HZ:
			case VMODE_1080P_50HZ:
			case VMODE_1080P_24HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
			case VMODE_1080P_23HZ:
#endif
			case VMODE_4K2K_30HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
			case VMODE_4K2K_29HZ:
#endif
			case VMODE_4K2K_25HZ:
			case VMODE_4K2K_24HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
			case VMODE_4K2K_23HZ:
#endif
			case VMODE_4K2K_SMPTE:
			case VMODE_VGA:
			case VMODE_SVGA:
			case VMODE_XGA:
			case VMODE_SXGA:
				vpu_mod = VPU_VENCP;
				break;
			case VMODE_480I:
			case VMODE_480I_RPT:
			case VMODE_576I:
			case VMODE_576I_RPT:
			case VMODE_480CVBS:
			case VMODE_576CVBS:
				vpu_mod = VPU_VENCI;
				break;
			case VMODE_LCD:
			case VMODE_LVDS_1080P:
			case VMODE_LVDS_1080P_50HZ:
				vpu_mod = VPU_VENCL;
				break;
			default:
				vpu_mod = VPU_MAX;
				break;
		}
