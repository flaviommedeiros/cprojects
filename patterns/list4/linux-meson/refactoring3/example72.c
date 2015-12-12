switch(mode)
	{
		case TVMODE_480I:
		case TVMODE_480I_RPT:
		case TVMODE_480CVBS:
		case TVMODE_576I:
		case TVMODE_576I_RPT:
		case TVMODE_576CVBS:
        aml_set_reg32_bits(P_VPU_VIU_VENC_MUX_CTRL, 1, 0, 2); //reg0x271a, select ENCI to VIU1
        aml_set_reg32_bits(P_VPU_VIU_VENC_MUX_CTRL, 1, 4, 4); //reg0x271a, Select encI clock to VDIN
        aml_set_reg32_bits(P_VPU_VIU_VENC_MUX_CTRL, 1, 8, 4); //reg0x271a,Enable VIU of ENC_I domain to VDIN;
			  break;
		case TVMODE_480P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_480P_59HZ:
#endif
		case TVMODE_480P_RPT:
		case TVMODE_576P:
		case TVMODE_576P_RPT:
		case TVMODE_720P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_720P_59HZ:
#endif
		case TVMODE_720P_50HZ:
		case TVMODE_1080I: //??
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_1080I_59HZ:
#endif
		case TVMODE_1080I_50HZ: //??
		case TVMODE_1080P:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_1080P_59HZ:
#endif
		case TVMODE_1080P_50HZ:
		case TVMODE_1080P_24HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_1080P_23HZ:
#endif
        case TVMODE_4K2K_30HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_4K2K_29HZ:
#endif
        case TVMODE_4K2K_25HZ:
        case TVMODE_4K2K_24HZ:
#ifdef CONFIG_AML_VOUT_FRAMERATE_AUTOMATION
		case TVMODE_4K2K_23HZ:
#endif
        case TVMODE_4K2K_SMPTE:
        case TVMODE_4K2K_FAKE_5G:
        case TVMODE_4K2K_60HZ:
		case TVMODE_VGA:
		case TVMODE_SVGA:
		case TVMODE_XGA:
		case TVMODE_SXGA:
		case TVMODE_WSXGA:
		case TVMODE_FHDVGA:
        default:
        aml_set_reg32_bits(P_VPU_VIU_VENC_MUX_CTRL, 2, 0, 2); //reg0x271a, select ENCP to VIU1
        aml_set_reg32_bits(P_VPU_VIU_VENC_MUX_CTRL, 2, 4, 4); //reg0x271a, Select encP clock to VDIN
        aml_set_reg32_bits(P_VPU_VIU_VENC_MUX_CTRL, 2, 8, 4); //reg0x271a,Enable VIU of ENC_P domain to VDIN;
        break;
	}
