if (cpu == 0 && IN_MEM(addr, BREAK_INSTR_SIZE, L1_CODE_START, L1_CODE_LENGTH))
		return 0;
#ifdef CONFIG_SMP
	else if (cpu == 1 && IN_MEM(addr, BREAK_INSTR_SIZE, COREB_L1_CODE_START, L1_CODE_LENGTH))
		return 0;
#endif
