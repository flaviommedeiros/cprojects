switch (len) {
	case 1:
		breakinfo[i].len = X86_BREAKPOINT_LEN_1;
		break;
	case 2:
		breakinfo[i].len = X86_BREAKPOINT_LEN_2;
		break;
	case 4:
		breakinfo[i].len = X86_BREAKPOINT_LEN_4;
		break;
#ifdef CONFIG_X86_64
	case 8:
		breakinfo[i].len = X86_BREAKPOINT_LEN_8;
		break;
#endif
	default:
		return -1;
	}
