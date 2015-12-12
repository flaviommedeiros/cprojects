if (gts->ri)
		GTP_REGS_PC(regs) = (CORE_ADDR)gts->ri->ret_addr;
#ifdef CONFIG_X86
	else if (GTP_X86_NEED_ADJUST_PC(gts))
		GTP_REGS_PC(regs) -= 1;
#endif
