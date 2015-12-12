switch (bp->attr.bp_len) {
	case HW_BREAKPOINT_LEN_1:
		info->len = X86_BREAKPOINT_LEN_1;
		break;
	case HW_BREAKPOINT_LEN_2:
		info->len = X86_BREAKPOINT_LEN_2;
		break;
	case HW_BREAKPOINT_LEN_4:
		info->len = X86_BREAKPOINT_LEN_4;
		break;
#ifdef CONFIG_X86_64
	case HW_BREAKPOINT_LEN_8:
		info->len = X86_BREAKPOINT_LEN_8;
		break;
#endif
	default:
		return -EINVAL;
	}
