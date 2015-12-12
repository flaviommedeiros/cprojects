static struct insn opcode_cc[] = {
#ifdef CONFIG_64BIT
	{ "brcth", 0x06, INSTR_RIL_RP },
	{ "aih", 0x08, INSTR_RIL_RI },
	{ "alsih", 0x0a, INSTR_RIL_RI },
	{ { 0, LONG_INSN_ALSIHN }, 0x0b, INSTR_RIL_RI },
	{ "cih", 0x0d, INSTR_RIL_RI },
	{ "clih", 0x0f, INSTR_RIL_RI },
#endif
	{ "", 0, INSTR_INVALID }
};
