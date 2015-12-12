static struct insn opcode_c6[] = {
#ifdef CONFIG_64BIT
	{ "crl", 0x0d, INSTR_RIL_RP },
	{ "cgrl", 0x08, INSTR_RIL_RP },
	{ "cgfrl", 0x0c, INSTR_RIL_RP },
	{ "chrl", 0x05, INSTR_RIL_RP },
	{ "cghrl", 0x04, INSTR_RIL_RP },
	{ "clrl", 0x0f, INSTR_RIL_RP },
	{ "clgrl", 0x0a, INSTR_RIL_RP },
	{ { 0, LONG_INSN_CLGFRL }, 0x0e, INSTR_RIL_RP },
	{ "clhrl", 0x07, INSTR_RIL_RP },
	{ { 0, LONG_INSN_CLGHRL }, 0x06, INSTR_RIL_RP },
	{ "pfdrl", 0x02, INSTR_RIL_UP },
	{ "exrl", 0x00, INSTR_RIL_RP },
#endif
	{ "", 0, INSTR_INVALID }
};
