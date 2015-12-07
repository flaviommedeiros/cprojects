#ifdef CONFIG_COMPAT
if (test_thread_flag(TIF_31BIT))
			per_info->control_regs.bits.ending_addr = 0x7fffffffUL;
		else
#endif
			per_info->control_regs.bits.ending_addr = PSW_ADDR_INSN;
