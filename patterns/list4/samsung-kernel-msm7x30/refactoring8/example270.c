static int
kgdb_set_hw_break(unsigned long addr, int len, enum kgdb_bptype bptype)
{
	int i;

	for (i = 0; i < HBP_NUM; i++)
		if (!breakinfo[i].enabled)
			break;
	if (i == HBP_NUM)
		return -1;

	switch (bptype) {
	case BP_HARDWARE_BREAKPOINT:
		len = 1;
		breakinfo[i].type = X86_BREAKPOINT_EXECUTE;
		break;
	case BP_WRITE_WATCHPOINT:
		breakinfo[i].type = X86_BREAKPOINT_WRITE;
		break;
	case BP_ACCESS_WATCHPOINT:
		breakinfo[i].type = X86_BREAKPOINT_RW;
		break;
	default:
		return -1;
	}
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
	breakinfo[i].addr = addr;
	if (hw_break_reserve_slot(i)) {
		breakinfo[i].addr = 0;
		return -1;
	}
	breakinfo[i].enabled = 1;

	return 0;
}
