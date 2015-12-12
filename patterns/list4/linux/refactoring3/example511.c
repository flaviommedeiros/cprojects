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
		/* AMD range breakpoint */
		if (!is_power_of_2(bp->attr.bp_len))
			return -EINVAL;
		if (bp->attr.bp_addr & (bp->attr.bp_len - 1))
			return -EINVAL;
		/*
		 * It's impossible to use a range breakpoint to fake out
		 * user vs kernel detection because bp_len - 1 can't
		 * have the high bit set.  If we ever allow range instruction
		 * breakpoints, then we'll have to check for kprobe-blacklisted
		 * addresses anywhere in the range.
		 */
		if (!cpu_has_bpext)
			return -EOPNOTSUPP;
		info->mask = bp->attr.bp_len - 1;
		info->len = X86_BREAKPOINT_LEN_1;
	}
