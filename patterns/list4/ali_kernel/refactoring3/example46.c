switch (hardware) {
#ifndef OPTi93X
	case OPTi9XX_HW_82C928:
	case OPTi9XX_HW_82C929:
		chip->mc_base = 0xf8c;
		chip->password = (hardware == OPTi9XX_HW_82C928) ? 0xe2 : 0xe3;
		chip->pwd_reg = 3;
		break;

	case OPTi9XX_HW_82C924:
	case OPTi9XX_HW_82C925:
		chip->mc_base = 0xf8c;
		chip->password = 0xe5;
		chip->pwd_reg = 3;
		break;
#else	/* OPTi93X */

	case OPTi9XX_HW_82C930:
	case OPTi9XX_HW_82C931:
	case OPTi9XX_HW_82C933:
		chip->mc_base = (hardware == OPTi9XX_HW_82C930) ? 0xf8f : 0xf8d;
		chip->mc_indir_index = 0xe0e;
		chip->password = 0xe4;
		chip->pwd_reg = 0;
		break;
#endif	/* OPTi93X */

	default:
		snd_printk(KERN_ERR "chip %d not supported\n", hardware);
		return -ENODEV;
	}
