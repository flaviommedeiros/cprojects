#ifdef CONFIG_THUMB2_KERNEL
if ((pc & 1) && !is_wide_instruction(*(u16 *)(pc - 1)))
		return pc + 2;
	else
#endif
	return pc + 4;
