switch (hbp_len) {
	case X86_BREAKPOINT_LEN_1:
		len_in_bytes = 1;
		break;
	case X86_BREAKPOINT_LEN_2:
		len_in_bytes = 2;
		break;
	case X86_BREAKPOINT_LEN_4:
		len_in_bytes = 4;
		break;
#ifdef CONFIG_X86_64
	case X86_BREAKPOINT_LEN_8:
		len_in_bytes = 8;
		break;
#endif
	}
