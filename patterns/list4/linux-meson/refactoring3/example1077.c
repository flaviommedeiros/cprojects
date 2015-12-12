switch (info->len) {
	case X86_BREAKPOINT_LEN_1:
		align = 0;
		break;
	case X86_BREAKPOINT_LEN_2:
		align = 1;
		break;
	case X86_BREAKPOINT_LEN_4:
		align = 3;
		break;
#ifdef CONFIG_X86_64
	case X86_BREAKPOINT_LEN_8:
		align = 7;
		break;
#endif
	default:
		return ret;
	}
