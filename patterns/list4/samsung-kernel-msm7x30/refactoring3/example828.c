switch (m68k_machtype) {
#ifdef CONFIG_AMIGA
	case MACH_AMIGA:
		config_amiga();
		break;
#endif
#ifdef CONFIG_ATARI
	case MACH_ATARI:
		config_atari();
		break;
#endif
#ifdef CONFIG_MAC
	case MACH_MAC:
		config_mac();
		break;
#endif
#ifdef CONFIG_SUN3
	case MACH_SUN3:
		config_sun3();
		break;
#endif
#ifdef CONFIG_APOLLO
	case MACH_APOLLO:
		config_apollo();
		break;
#endif
#ifdef CONFIG_MVME147
	case MACH_MVME147:
		config_mvme147();
		break;
#endif
#ifdef CONFIG_MVME16x
	case MACH_MVME16x:
		config_mvme16x();
		break;
#endif
#ifdef CONFIG_BVME6000
	case MACH_BVME6000:
		config_bvme6000();
		break;
#endif
#ifdef CONFIG_HP300
	case MACH_HP300:
		config_hp300();
		break;
#endif
#ifdef CONFIG_Q40
	case MACH_Q40:
		config_q40();
		break;
#endif
#ifdef CONFIG_SUN3X
	case MACH_SUN3X:
		config_sun3x();
		break;
#endif
#ifdef CONFIG_COLDFIRE
	case MACH_M54XX:
		config_BSP(NULL, 0);
		break;
#endif
	default:
		panic("No configuration setup");
	}
